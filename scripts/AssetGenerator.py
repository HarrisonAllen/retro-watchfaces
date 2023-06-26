import os
import glob
import sys
from PIL import Image
import math

TILE_SIZE = 8
COLORS_PER_PALETTE = 16
NUM_PALETTES = 8
C_FILE_HEADER = "#pragma once\n\n#include <pebble.h>\n\n"
NUMBERS = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ":"]
NUMBER_WIDTH = 3
NUMBER_HEIGHT = 5

def check_if_image_in_list(source_list, image):
    for source_image in source_list:
        if list(source_image.getdata()) == list(image.getdata()):
            return True
    return False

def make_attribute(palette=0, vram_bank=0, x_flip=0, y_flip=0, hide=0):
    return palette | (vram_bank << 3) | (x_flip << 5) | (y_flip << 6) | (hide << 7)

def generate_tilesheet(tiles, palettes, tile_palettes):
    tilesheet_bytestring = ""
    for tile, palette_num in zip(tiles, tile_palettes):
        tile_bytestring = ""
        for y in range(tile.size[1]):
            for x in range(tile.size[0]):
                pixel = tile.convert("RGBA").getpixel((x,y))
                if pixel[3] == 0:
                    pixel = (0, 0, 0, 0)

                tile_bytestring += format(palettes[palette_num].index(pixel), '04b')
        tilesheet_bytestring += tile_bytestring
    return int(tilesheet_bytestring, 2).to_bytes((len(tilesheet_bytestring) + 7) // 8, byteorder="big")

def generate_sprite_data_structure(sprites, sprite_image_palettes):
    sprite_defines = ""
    for i in range(len(sprites)):
        sprite = sprites[i]
        sprite_defines += f"#define {sprite[0]} {i}\n"

    sprite_data_structure = "uint8_t SPRITE_DATA[][8] = {\n"
        # e.g.MarioBig_Walk = {num, x, y, tile, [attr byte], width, height, mos_x, mos_y}
    sprite_data_structure += "    // {x, y, vram tile start, attributes, width, height, mosaic x, mosaic y}\n"
    for i in range(len(sprites)):
        sprite = sprites[i]
        sprite_data_structure += f"    {{0, 0, {sprite[1]}, 0b{format(make_attribute(palette=sprite_image_palettes[i], vram_bank=1), '08b')}, {sprite[2]}, {sprite[3]}, 0, 0}}, // {sprite[0]}\n"
    sprite_data_structure += "};"
    return C_FILE_HEADER + sprite_defines + "\n" + sprite_data_structure

def convert_rgba_to_pebble_color(color):
    pebble_color = "0b11" # A
    pebble_color += format(color[0] // 85, '02b') # R
    pebble_color += format(color[1] // 85, '02b') # G
    pebble_color += format(color[2] // 85, '02b') # B
    return pebble_color

def generate_palette_data_structure(bg_palettes, sprite_palettes):
    bg_palette_data_structure = f"uint8_t BG_PALETTES[][{COLORS_PER_PALETTE}] = {{\n"
    for palette in bg_palettes:
        bg_palette_data_structure += "    {"
        for i in range(COLORS_PER_PALETTE):
            if i >= len(palette):
                color = (0, 0, 0, 0)
            else:
                color = palette[i]
            bg_palette_data_structure += f"{convert_rgba_to_pebble_color(color)}, "
        bg_palette_data_structure += "},\n"
    bg_palette_data_structure += "};\n"
    
    sprite_palette_data_structure = f"uint8_t SPRITE_PALETTES[][{COLORS_PER_PALETTE}] = {{\n"
    for palette in sprite_palettes:
        sprite_palette_data_structure += "    {"
        for i in range(COLORS_PER_PALETTE):
            if i >= len(palette):
                color = (0, 0, 0, 0)
            else:
                color = palette[i]
            sprite_palette_data_structure += f"{convert_rgba_to_pebble_color(color)}, "
        sprite_palette_data_structure += "},\n"
    sprite_palette_data_structure += "};\n"

    return C_FILE_HEADER + bg_palette_data_structure + "\n" + sprite_palette_data_structure

def generate_number_data_structure(numbers):
    number_defines = f"#define NUMBER_WIDTH {NUMBER_WIDTH}\n#define NUMBER_HEIGHT {NUMBER_HEIGHT}\n"
    number_tile_data_structure = f"uint8_t NUMBER_TILES[][{NUMBER_WIDTH * NUMBER_HEIGHT}] = {{\n"
    for n in NUMBERS:
        number_tile_data_structure += f"    {{ // {n}\n"
        number_tile_data = numbers[n][0]
        for y in range(NUMBER_HEIGHT):
            number_tile_data_structure += "        "
            for x in range(NUMBER_WIDTH):
                number_tile_data_structure += f"{number_tile_data[x + y * NUMBER_WIDTH]}, "
            number_tile_data_structure += "\n"
        number_tile_data_structure += f"    }},\n"
    number_tile_data_structure += "};\n"
    
    number_attr_data_structure = f"uint8_t NUMBER_ATTRS[][{NUMBER_WIDTH * NUMBER_HEIGHT}] = {{\n"
    for n in NUMBERS:
        number_attr_data_structure += f"    {{ // {n}\n"
        number_palette_data = numbers[n][1]
        for y in range(NUMBER_HEIGHT):
            number_attr_data_structure += "        "
            for x in range(NUMBER_WIDTH):
                number_attr_data_structure += f"0b{format(make_attribute(palette=number_palette_data[x + y * NUMBER_WIDTH]), '08b')}, "
            number_attr_data_structure += "\n"
        number_attr_data_structure += f"    }},\n"
    number_attr_data_structure += "};\n"

    return C_FILE_HEADER + number_defines + "\n" + number_tile_data_structure + "\n" + number_attr_data_structure



def write_tilesheet_to_file(tilesheet, filename):
    with open(filename, "wb") as f_out:
        f_out.write(tilesheet)

def write_string_to_file(string, filename):
    with open(filename, "w") as f_out:
        f_out.write(string)

def write_map_to_file(map, filename):
    with open(filename, "wb") as f_out:
        f_out.write(bytes(map))


class Converter:
    def __init__(self, directory):
        self.directory = directory
        self.output_directory = os.path.join(self.directory, "Output")
        if os.path.exists(self.output_directory):
            files = glob.iglob(os.path.join(self.output_directory,'*'))
            for f in files:
                os.remove(f)
            pass
        else:
            os.makedirs(self.output_directory)

        self.bg_tiles = []
        self.sprite_tiles = []
        self.sprites = []

    def convert(self):
        print(f"Converting from {self.directory}")
        background_image_filenames = glob.iglob(os.path.join(self.directory, "Background*.png"))
        for background_image_filename in background_image_filenames:
            self.bg_tiles = self.extract_bg_tiles(background_image_filename, self.bg_tiles)
        
        number_image_filename = os.path.join(self.directory, "Numbers.png")
        self.bg_tiles = self.extract_bg_tiles(number_image_filename, self.bg_tiles)

        print(f"Total of {len(self.bg_tiles)} bg tiles")

        background_palettes = self.extract_palettes_from_images(self.bg_tiles)
        bg_tile_palettes = self.assign_palettes_to_images(self.bg_tiles, background_palettes)

        bg_tilemaps = []
        bg_attrmaps = []
        background_image_filenames = glob.iglob(os.path.join(self.directory, "Background*.png"))
        for background_image_filename in background_image_filenames:
            tilemap, attrmap = self.generate_tilemap_and_attrmap(background_image_filename, bg_tile_palettes, self.bg_tiles)
            bg_tilemaps.append(tilemap)
            bg_attrmaps.append(attrmap)

        for i in range(len(bg_tilemaps)):
            write_map_to_file(bg_tilemaps[i], os.path.join(self.output_directory, f"Background_{i}_tilemap.bin"))
            write_map_to_file(bg_attrmaps[i], os.path.join(self.output_directory, f"Background_{i}_attrmap.bin"))

        # Generate tile bits, 4bpp
        bg_tilesheet = generate_tilesheet(self.bg_tiles, background_palettes, bg_tile_palettes)
        write_tilesheet_to_file(bg_tilesheet, os.path.join(self.output_directory, "BG_Tilesheet.bin"))

        # Build numbers, which will be a data structure that has tile and attrs,
        # And then load into an array i guess. Build numbers l->r t->b
        number_image_filename = os.path.join(self.directory, "Numbers.png")
        number_map = self.generate_number_map(number_image_filename, self.bg_tiles, bg_tile_palettes)
        number_data_structure = generate_number_data_structure(number_map)
        write_string_to_file(number_data_structure, os.path.join(self.output_directory, "Numbers.h"))

        # Generate sprites which will be stored with their sprite bytes
        sprite_image_filenames = glob.iglob(os.path.join(self.directory, "Sprites/*.png"))
        sprite_images = [Image.open(image_filename) for image_filename in sprite_image_filenames]
        sprite_palettes = self.extract_palettes_from_images(sprite_images)
        sprite_image_palettes = self.assign_palettes_to_images(sprite_images, sprite_palettes)

        sprite_num = 0
        sprite_tile_palettes = []
        sprite_image_filenames = glob.iglob(os.path.join(self.directory, "Sprites/*.png"))
        for sprite_image_filename in sprite_image_filenames:
            self.sprite_tiles, self.sprites = self.extract_sprite_tiles(sprite_image_filename, self.sprite_tiles, self.sprites)
            for i in range(self.sprites[-1][2] * self.sprites[-1][3]):
                sprite_tile_palettes.append(sprite_image_palettes[sprite_num])
            sprite_num += 1

        sprite_tilesheet = generate_tilesheet(self.sprite_tiles, sprite_palettes, sprite_tile_palettes)
        write_tilesheet_to_file(sprite_tilesheet, os.path.join(self.output_directory, "Sprite_Tilesheet.bin"))

        sprite_data_structure = generate_sprite_data_structure(self.sprites, sprite_image_palettes)
        write_string_to_file(sprite_data_structure, os.path.join(self.output_directory, "Sprites.h"))

        palette_data_structure = generate_palette_data_structure(background_palettes, sprite_palettes)
        write_string_to_file(palette_data_structure, os.path.join(self.output_directory, "Palettes.h"))

    def extract_bg_tiles(self, image_filename, tiles):
        print(f"Extracting tiles from {image_filename}")
        image = Image.open(image_filename)
        dims = image.size

        total_count = 0
        kept_count = 0

        for y in range(0, dims[1], TILE_SIZE):
            for x in range(0, dims[0], TILE_SIZE):
                tile = image.crop((x, y, x + TILE_SIZE, y + TILE_SIZE))
                if not check_if_image_in_list(tiles, tile):
                    tiles.append(tile)
                    kept_count += 1
                total_count += 1

        return tiles

    def extract_sprite_tiles(self, image_filename, tiles, sprites):
        print(f"Extracting tiles from {image_filename}")

        image = Image.open(image_filename)
        dims = image.size

        sprites.append([
            os.path.splitext(os.path.basename(image_filename))[0], 
            len(tiles), 
            # width = TILE_SIZE * (2 ** sprite_width)
            # (width / tile_size) = 2 ** sprite_width
            # log2(width / tile_size) == sprite_width
            round(math.log2(dims[0] // TILE_SIZE)), 
            round(math.log2(dims[1] // TILE_SIZE))
        ])
        
        for y in range(0, dims[1], TILE_SIZE):
            for x in range(0, dims[0], TILE_SIZE):
                tile = image.crop((x, y, x + TILE_SIZE, y + TILE_SIZE))
                tiles.append(tile)
        
        return tiles, sprites


    def generate_tilesheet_image(self, tiles):
        dims = (len(tiles) * TILE_SIZE, TILE_SIZE)

        tilesheet = Image.new("RGBA", dims)
        for x in range(len(tiles)):
            tilesheet.paste(tiles[x], (x * TILE_SIZE, 0))

        return tilesheet
    
    def generate_tilemap_and_attrmap(self, background_filenames, palettes, tiles):
        tilemap = []
        attrmap = []
        image = Image.open(background_filenames)
        dims = image.size

        for y in range(0, dims[1], TILE_SIZE):
            for x in range(0, dims[0], TILE_SIZE):
                tile = image.crop((x, y, x + TILE_SIZE, y + TILE_SIZE))
                for i in range(len(tiles)):
                    if list(tile.getdata()) == list(tiles[i].getdata()):
                        tilemap.append(i)
                        attrmap.append(make_attribute(palette=palettes[i]))
        return tilemap, attrmap
    
    def generate_number_map(self, number_filename, tiles, tile_palettes):
        number_image = Image.open(number_filename)
        
        numbers = {}

        for n in range(len(NUMBERS)):
            number_tiles = []
            number_palettes = []
            x_start = TILE_SIZE * NUMBER_WIDTH * n
            for y in range(0, TILE_SIZE * NUMBER_HEIGHT, TILE_SIZE):
                for x in range(x_start, x_start + TILE_SIZE * NUMBER_WIDTH, TILE_SIZE):
                    tile = number_image.crop((x, y, x + TILE_SIZE, y + TILE_SIZE))
                    for i in range(len(tiles)):
                        if list(tile.getdata()) == list(tiles[i].getdata()):
                            number_tiles.append(i)
                            number_palettes.append(tile_palettes[i])
            numbers[NUMBERS[n]] = (number_tiles, number_palettes)
        return numbers

    
    def extract_palettes_from_images(self, images):
        palettes = []
        for i in range(NUM_PALETTES):
            palettes.append(set())
            palettes[-1].add((0, 0, 0, 0))
        for image in images:
            colors = image.convert("RGBA").getcolors()
            image_colors = set()
            for _count, color in colors:
                if color[3] == 0:
                    color = (0, 0, 0, 0)
                image_colors.add(color)
            
            for palette in palettes:
                if len(image_colors | palette) <= COLORS_PER_PALETTE:
                    palette |= image_colors
                    break

        return [sorted(list(p)) for p in palettes]
    
    def assign_palettes_to_images(self, images, palettes):
        assignments = []
        
        for image in images:
            colors = image.convert("RGBA").getcolors()
            image_colors = set()
            for _count, color in colors:
                if color[3] == 0:
                    color = (0, 0, 0, 0)
                image_colors.add(color)
            
            for i in range(len(palettes)):
                if image_colors.issubset(set(palettes[i])):
                    assignments.append(i)
                    break
        
        return assignments






        

if __name__ == "__main__":
    directory = sys.argv[1]
    
    Converter(directory).convert()