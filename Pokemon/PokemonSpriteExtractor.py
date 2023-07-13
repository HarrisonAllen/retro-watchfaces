import glob
import math
import os
import shutil
import sys
from PIL import Image, ImageDraw, ImageFilter
import re

NUM_POKEMON = 815
NUM_SPRITES_PER_IMAGE_X = 4
NUM_SPRITES_PER_IMAGE_Y = 4
SPRITE_DIRECTIONS = ["D", "L", "R", "U"]
TILE_WIDTH = 8
TILE_HEIGHT = 8
NUM_PALETTES = 8
COLORS_PER_PALETTE = 16

# Need a folder for the images with 4 x 4 sprites
# Frame  1   1   2   2
# Down  [ ] [ ] [ ] [ ]
# Left  [ ] [ ] [ ] [ ]
# Right [ ] [ ] [ ] [ ]
# Up    [ ] [ ] [ ] [ ]
# The plan:
# Split each image equally into 4x4 chunks
# Then grab (1, 3) and (3, 3) (x, y) (col, row)
# Frame  1   1   2   2
# Down  [ ] [ ] [ ] [ ]
# Left  [ ] [ ] [ ] [ ]
# Right [X] [ ] [X] [ ]
# Up    [ ] [ ] [ ] [ ]
# These two sprites are what we want for walking right
# Manually add a bounce up and down between frames
# Frame:  1 1 2 2
# Height: _ - _ -

# For filename, we only want:
# ###_0.png, e.g. 014_0.png
# Could do ###.png, too
# Oh it looks like if I want to add unknown support the regex needs to be:
# ###_#*.png where there can be a whatever amount of numbers after the underscore
# want to avoid shiny, which is ###s_#.png
# However steelix has 2 sprites which are exactly the same, 208_0 and 208_1
# And heracross (214_0, 214_1)
# Ohhhh but then alternate forms also use that, like shaymin (492_0, 492_1), giratina (487_0, 487_1), arceus has a lot
# Buuuuut once we get to gen 5 there are no more ###_# s. It becomes only ###.png, ###s.png
# some of the shinies don't have transparent backgrounds (I don't plan on doing them anyway)
# Ohhhh the _ do make a reappearance when forms come back, like 669_ (idk the pokemon lol) BUT there is no 669_0, only 669_1+
# So, we grep all of the e.g. 669*, filter out non-number characters (except _), filter out _0 if there is a ###.png

# Some things I might want to keep track of for data:
# * Count of how many of each size there are
# * Which ones I'm grabbing _1+ of and check to make sure they're actually unique (e.g. steelix) then manually delete
#   or i could write a removal script speaking of which:

# New plan: extract everything
# Frame  1   1   2   2
# Down  [X] [ ] [X] [ ]
# Left  [X] [ ] [X] [ ]
# Right [X] [ ] [X] [ ]
# Up    [X] [ ] [X] [ ]
def extract_sprites(input_directory, output_directory):
    # Setup output directory
    print("Setting up output directory...")
    if os.path.exists(output_directory):
        shutil.rmtree(output_directory)
    os.makedirs(output_directory)

    print("Extracting pokemon...")
    total_pokemon = 0
    for number in range(1, NUM_POKEMON + 1):
        padded_number = str(number).zfill(3)
        print(f"Extracting {padded_number}/{NUM_POKEMON}...")
        glob_filter = os.path.join(input_directory, f"{padded_number}*.png")
        pokemon_filenames = glob.glob(glob_filter)

        pokemon_file_directory = os.path.join(output_directory, padded_number)
        os.makedirs(pokemon_file_directory)
        for pokemon_file in pokemon_filenames:
            total_pokemon += 1
            pokemon_image = Image.open(pokemon_file)
            pokemon_image_basename = os.path.basename(pokemon_file).split(".")[0]
            
            pokemon_subdirectory = os.path.join(pokemon_file_directory, pokemon_image_basename)
            os.makedirs(pokemon_subdirectory)

            dims = pokemon_image.size

            sprite_width = dims[0] // NUM_SPRITES_PER_IMAGE_X
            sprite_height = dims[1] // NUM_SPRITES_PER_IMAGE_Y

            pokemon_sprites = []

            for x in range(0, dims[0], sprite_width):
                for y in range(0, dims[1], sprite_height):
                    sprite = pokemon_image.crop((x, y, x + sprite_width, y + sprite_height))
                    pokemon_sprites.append(sprite)
            
            for x in range(2):
                for y in range(NUM_SPRITES_PER_IMAGE_X):
                    sprite_filename = f"{pokemon_image_basename}_{SPRITE_DIRECTIONS[y]}_{x}.png"
                    sprite = pokemon_sprites[y + x * NUM_SPRITES_PER_IMAGE_X * 2]
                    sprite.save(os.path.join(pokemon_subdirectory, sprite_filename))
    print(f"Extraction Complete! (Extracted {total_pokemon} pokemon)")

# Requires all images to be the same size
def alpha_composite_images(images):
    output_image = Image.new("RGBA", images[0].size)
    for image in images:
        if not image.mode == "RGBA":
            image = image.convert("RGBA")
        output_image = Image.alpha_composite(output_image, image)
    return output_image

def crop_sprites(input_directory, output_directory):
    # Setup output directory
    print("Setting up output directory...")
    if os.path.exists(output_directory):
        shutil.rmtree(output_directory)
    os.makedirs(output_directory)

    print("Cropping pokemon...")
    glob_filter = os.path.join(input_directory, "*/")
    pokemon_directories = glob.glob(glob_filter)

    size_count = {}

    for pokemon_directory in pokemon_directories:
        pokemon_output_directory = os.path.join(output_directory, os.path.basename(os.path.dirname(pokemon_directory)))
        os.makedirs(pokemon_output_directory)

        glob_filter = os.path.join(pokemon_directory, "*/")
        pokemon_sub_directories = glob.glob(glob_filter)

        for pokemon_sub_directory in pokemon_sub_directories:
            print(f"Cropping {os.path.basename(os.path.dirname(pokemon_sub_directory))}... ", end="")
            
            pokemon_output_sub_directory = os.path.join(pokemon_output_directory, os.path.basename(os.path.dirname(pokemon_sub_directory)))
            os.makedirs(pokemon_output_sub_directory)

            glob_filter = os.path.join(pokemon_sub_directory, "*.png")
            pokemon_filenames = glob.glob(glob_filter)

            pokemon_images = [Image.open(pf) for pf in pokemon_filenames]
            merged_image = alpha_composite_images(pokemon_images)

            bounds = merged_image.getbbox()

            x = bounds[0]
            y = bounds[1]
            w = bounds[2] - bounds[0]
            h = bounds[3] - bounds[1]

            tiled_w = math.ceil(w / TILE_WIDTH) * TILE_WIDTH
            tiled_h = math.ceil(h / TILE_HEIGHT) * TILE_HEIGHT
            tiled_x = x - (tiled_w - w) / 2
            tiled_y = y - (tiled_h - h) / 2
            tiled_bounds = (tiled_x, tiled_y, tiled_x + tiled_w, tiled_y + tiled_h)
            # if bounds != tiled_bounds:
            #     draw = ImageDraw.Draw(merged_image)
            #     draw.rectangle(bounds, outline=(255, 0, 0))
            #     print(f"Bounds: {bounds}, {(w, h)}")
            #     draw.rectangle(tiled_bounds, outline=(0, 0, 255))
            #     print(f"Tiled bounds: {tiled_bounds}, {(tiled_w, tiled_h)}")
            #     merged_image.show()
            #     return
            
            for filename, image in zip(pokemon_filenames, pokemon_images):
                save_filename = os.path.join(pokemon_output_sub_directory, os.path.basename(filename))
                cropped_image = image.crop(tiled_bounds)
                cropped_image.save(save_filename)
                
            if bounds != tiled_bounds:
                print(f"\t{(w, h)} -> {(tiled_w, tiled_h)}")
            else:
                print(f"\t{(w, h)}")
            size_count[(tiled_w, tiled_h)] = size_count.get((tiled_w, tiled_h), 0) + 1
    
    for dims in sorted(size_count.keys(), key=sum):
        print(f"{(dims[0]//TILE_WIDTH, dims[1]//TILE_HEIGHT)}: {size_count[dims]}")
    
    print("Cropping complete!")
        

# Conversion:
# * Filter out what we don't want (shinies, duplicates, weird ones)
# * Create some binary files:
#   1. A massive tilesheet with every pokemon
#   2. A mapping of where the sprites are in the tilesheet
#      e.g. 125: 15835 tiles
#   3. 1 Palette for each pokemon
#   4. Maybe this one allows for regex filters hmm
# * Plop into folders
# * Colors: color = round(color / 85) * 85

def convert_rgba_to_pebble_palette(color):
    r = round(color[0] / 85) * 85
    g = round(color[1] / 85) * 85
    b = round(color[2] / 85) * 85
    return (r, g, b, 255)

def convert_images_to_pebble_colors(images):
    converted_images = []
    for image in images:
        transparent_image = image
        pixels = transparent_image.load()
        for x in range(transparent_image.size[0]):
            for y in range(transparent_image.size[1]):
                if pixels[x,y][-1] < 128:
                    pixels[x,y] = (0, 0, 0, 0)
                else:
                    pixels[x,y] = convert_rgba_to_pebble_palette(pixels[x,y])
        # result = transparent_image.convert('P', colors=16)
        converted_images.append(transparent_image)
    return converted_images

def extract_palettes_from_images(images):
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
            print("WARNING: TOO MANY COLORS")
    return [sorted(list(p)) for p in palettes]

def extract_palette_from_images(images, attempts=10):
    if attempts == 0:
        images[0].show()
        raise RecursionError("Too deep bucko")
    palette = set()
    palette.add((0, 0, 0, 0))
    for image in images:
        colors = image.convert("RGBA").getcolors()
        if not colors:
            image.show()
            image.convert("RGBA").show()
        image_colors = set()
        for _count, color in colors:
            if color[3] == 0:
                color = (0, 0, 0, 0)
            image_colors.add(color)
        
        if len(image_colors | palette) <= COLORS_PER_PALETTE:
            palette |= image_colors
            continue
        else:
            print("Gotta go deeper")
            return extract_palette_from_images([im.convert('P', palette=Image.ADAPTIVE, colors=len(im.getcolors())-2) for im in images], attempts-1)
    return sorted(list(palette)), images

def extract_tiles_from_images(images):
    tiles = []
    for image in images:
        dims = image.size
        for y in range(0, dims[1], TILE_HEIGHT):
            for x in range(0, dims[0], TILE_WIDTH):
                tile = image.crop((x, y, x + TILE_WIDTH, y + TILE_HEIGHT))
                tiles.append(tile)
    return tiles

def append_tiles_to_tilesheet(tilesheet_filename, tiles, palette):
    tilesheet_bytestring = ""
    for tile in tiles:
        tile_bytestring = ""
        for y in range(tile.size[1]):
            for x in range(tile.size[0]):
                pixel = tile.convert("RGBA").getpixel((x,y))
                if pixel[3] == 0:
                    pixel = (0, 0, 0, 0)
                tile_bytestring += format(palette.index(pixel), '04b')
        tilesheet_bytestring += tile_bytestring
    with open(tilesheet_filename, "ab") as f_out:
        f_out.write(int(tilesheet_bytestring, 2).to_bytes((len(tilesheet_bytestring) + 7) // 8, byteorder="big"))

def convert_rgba_to_pebble_color(color):
    pebble_color = 0b11000000
    pebble_color += round(color[0] / 85) << 4 # R
    pebble_color += round(color[1] / 85) << 2 # G
    pebble_color += round(color[2] / 85) << 0 # Bs
    return pebble_color

def create_sprite_palette_bytes(palette):
    palette_array = []
    for i in range(COLORS_PER_PALETTE):
        if i >= len(palette):
            color = (0, 0, 0, 0)
        else:
            color = palette[i]
        palette_array.append(convert_rgba_to_pebble_color(color))
    return bytes(palette_array)

def convert_rgba_to_bw_pebble_color(color):
    color_sum = 0
    color_sum += color[0] / 85 # R
    color_sum += color[1] / 85 # G
    color_sum += color[2] / 85 # B
    color_average = round(color_sum / 3)
    if color_average > 0:
        color_average = min(color_average + 1, 0b11)
    return color_average

def create_sprite_bw_palette_bytes(palette):
    palette_array = []
    for i in range(COLORS_PER_PALETTE):
        if i >= len(palette):
            color = (0, 0, 0, 0)
        else:
            color = palette[i]
        palette_array.append(convert_rgba_to_bw_pebble_color(color))
    return bytes(palette_array)

def append_sprite_data_to_file(sprite_data_filename, sprite_tilesheet_offset_bytes, sprite_dims_byte, sprite_palette_bytes):
    with open(sprite_data_filename, "ab") as f_out:
        f_out.write(sprite_tilesheet_offset_bytes)
        f_out.write(sprite_dims_byte)
        f_out.write(sprite_palette_bytes)

def append_sprite_name_to_list(sprite_list_filename, sprite_name):
    with open(sprite_list_filename, "a") as f_out:
        f_out.write(sprite_name + "\n")

def add_outline_to_images(images):
    outlined_images = []
    for image in images:
        image = image.convert("RGBA")
        outline = image.filter(ImageFilter.FIND_EDGES).convert("RGBA")
        data = outline.getdata()

        new_data = []
        for item in data:
            if item[3] != 0:
                new_data.append((0, 0, 0, 255))
            else:
                new_data.append((0, 0, 0, 0))

        outline.putdata(new_data)
        outlined_images.append(alpha_composite_images([image, outline]))
    return outlined_images

FILTER_BLACKLIST = [
    "003_1", # Not different enough
    "154_1", # Not different enough
    "208_1", # Not different enough 
    "214_1", # Not different enough
    "385_1", # No difference
    "649_1", # No difference
    "649_2", # No difference
    "649_3", # No difference
    "649_4", # No difference
    "201_1", # No difference sideways
    "201_2", # No difference sideways
    "201_3", # No difference sideways
    "201_4", # No difference sideways
    "201_5", # No difference sideways
    "201_6", # No difference sideways
    "201_7", # No difference sideways
    "201_8", # No difference sideways
    "201_9", # No difference sideways
    "201_10", # No difference sideways
    "201_11", # No difference sideways
    "201_12", # No difference sideways
    "201_13", # No difference sideways
    "201_14", # No difference sideways
    "201_15", # No difference sideways
    "201_16", # No difference sideways
    "201_17", # No difference sideways
    "201_18", # No difference sideways
    "201_19", # No difference sideways
    "201_20", # No difference sideways
    "201_21", # No difference sideways
    "201_22", # No difference sideways
    "201_23", # No difference sideways
    "201_24", # No difference sideways
    "201_25", # No difference sideways
    "201_26", # No difference sideways
    "201_27", # No difference sideways
    "443_1", # Not different enough
    "444_1", # No difference
    "445_1", # Not different enough
    "494_1", # No difference
]

FILTER_WHITELIST = [
    "585-at",
    "585-sp",
    "585-wt",
    "586(at)",
    "586-sp",
    "586-wt",
    "592(female)",
    "593(F)",
    "648_p"
]

LAST_NUMBER_IN_EACH_GENERATION = [151, 251, 386, 493, 649, 721, 815]

def convert_sprites(input_directory, output_directory):
    # Setup output directory
    print("Setting up output directory...")
    if os.path.exists(output_directory):
        shutil.rmtree(output_directory)
    os.makedirs(output_directory)

    print("Converting pokemon...")
    glob_filter = os.path.join(input_directory, "*/")
    pokemon_directories = glob.glob(glob_filter)


    test_directory = os.path.join(output_directory, "ConvertedImages")
    os.makedirs(test_directory)
    num_sprites = 0
    tilesheet_offset = 0
    tiles_per_generation = []
    sprites_per_generation = []
    current_gen = 0

    generation_directory = os.path.join(output_directory, f"Generation_{current_gen+1}")
    os.makedirs(generation_directory)

    sprite_tilesheet_filename = os.path.join(generation_directory, "SpriteTilesheet.bin")
    open(sprite_tilesheet_filename, "wb").close()
    sprite_tilesheet_bw_filename = os.path.join(generation_directory, "SpriteTilesheet~bw.bin")
    open(sprite_tilesheet_bw_filename, "wb").close()
    sprite_data_filename = os.path.join(generation_directory, "SpriteData.bin")
    open(sprite_data_filename, "wb").close()
    sprite_data_bw_filename = os.path.join(generation_directory, "SpriteData~bw.bin")
    open(sprite_data_bw_filename, "wb").close()
    sprite_list_filename = os.path.join(generation_directory, "SpriteList.txt")
    open(sprite_list_filename, "w").close()
    sprite_image_directory = os.path.join(generation_directory, f"SpriteImages")
    os.makedirs(sprite_image_directory)
    sprite_image_bw_directory = os.path.join(generation_directory, f"SpriteImages~bw")
    os.makedirs(sprite_image_bw_directory)

    for pokemon_directory in pokemon_directories:
        # pokemon_output_directory = os.path.join(output_directory, os.path.basename(os.path.dirname(pokemon_directory)))
        # os.makedirs(pokemon_output_directory)
        pokemon_number = os.path.basename(os.path.dirname(pokemon_directory))

        glob_filter = os.path.join(pokemon_directory, "*/")
        pokemon_sub_directories = glob.glob(glob_filter)

        for pokemon_sub_directory in pokemon_sub_directories:
            
            pokemon_sub_number = os.path.basename(os.path.dirname(pokemon_sub_directory))
            if not (pokemon_sub_number in FILTER_WHITELIST or (pokemon_sub_number not in FILTER_BLACKLIST and re.fullmatch("\d{3}(_[1-9]+\d*)*\/", pokemon_sub_number+"/"))):
                continue
            print(f"Converting {pokemon_sub_number}...")
                
            glob_filter = os.path.join(pokemon_sub_directory, "*.png")
            pokemon_filenames = glob.glob(glob_filter)
            pokemon_images = [Image.open(pf) for pf in pokemon_filenames][4:6]
            resized_images = [image.resize((image.size[0] // 2, image.size[1] // 2), resample=Image.NEAREST) for image in pokemon_images]
            
            # Re-crop this imsage
            merged_image = alpha_composite_images(resized_images)

            bounds = merged_image.getbbox()

            x = bounds[0]
            y = bounds[1]
            w = bounds[2] - bounds[0]
            h = bounds[3] - bounds[1]
            bottom_y = bounds[3]

            tiled_w = math.ceil(w / TILE_WIDTH) * TILE_WIDTH
            tiled_h = math.ceil(h / TILE_HEIGHT) * TILE_HEIGHT
            tiled_x = x - (tiled_w - w) / 2 # Center the x
            tiled_y = bottom_y - tiled_h # And put the feet of the sprite on the lowest pixel
            tiled_bounds = (tiled_x, tiled_y, tiled_x + tiled_w, tiled_y + tiled_h)
            cropped_images = [image.crop(tiled_bounds) for image in resized_images]

            # if (pokemon_images[0].size[0] > 48 or pokemon_images[0].size[1] > 48):
            #     continue
            converted_images = convert_images_to_pebble_colors(cropped_images)
            pokemon_palette, final_pokemon_images = extract_palette_from_images(converted_images)
            outlined_images = add_outline_to_images(cropped_images)
            converted_bw_images = convert_images_to_pebble_colors(outlined_images)
            bw_pokemon_palette, bw_pokemon_images = extract_palette_from_images(converted_bw_images)
            for i in range(len(final_pokemon_images)):
                final_pokemon_images[i].save(os.path.join(sprite_image_directory, f"{pokemon_sub_number}_{i}.png"))
                bw_pokemon_images[i].save(os.path.join(sprite_image_bw_directory, f"{pokemon_sub_number}_{i}.png"))

            # print(f"\t{len(pokemon_palette)} colors")
            
            pokemon_tiles = extract_tiles_from_images(final_pokemon_images)
            # Append tiles to a generation tilesheet
            append_tiles_to_tilesheet(sprite_tilesheet_filename, pokemon_tiles, pokemon_palette)
            # Append sprite data to a generation sprite sheet
            sprite_tilesheet_offset_bytes = tilesheet_offset.to_bytes(2, "big")
            sprite_width = final_pokemon_images[0].size[0] // TILE_WIDTH - 1
            sprite_height = final_pokemon_images[0].size[1] // TILE_HEIGHT - 1
            sprite_dims_byte = int(sprite_width | (sprite_height << 4)).to_bytes(1, "big")
            sprite_palette_bytes = create_sprite_palette_bytes(pokemon_palette)
            append_sprite_data_to_file(sprite_data_filename, sprite_tilesheet_offset_bytes, sprite_dims_byte, sprite_palette_bytes)
            
            # Do it again for bw
            bw_pokemon_tiles = extract_tiles_from_images(bw_pokemon_images)
            # Append tiles to a generation tilesheet
            append_tiles_to_tilesheet(sprite_tilesheet_bw_filename, bw_pokemon_tiles, bw_pokemon_palette)
            # Append sprite data to a generation sprite sheet
            sprite_tilesheet_offset_bytes = tilesheet_offset.to_bytes(2, "big")
            sprite_width = bw_pokemon_images[0].size[0] // TILE_WIDTH - 1
            sprite_height = bw_pokemon_images[0].size[1] // TILE_HEIGHT - 1
            sprite_dims_byte = int(sprite_width | (sprite_height << 4)).to_bytes(1, "big")
            # Append black and white sprite data to a generation sprite sheet
            sprite_bw_palette_bytes = create_sprite_bw_palette_bytes(bw_pokemon_palette)
            append_sprite_data_to_file(sprite_data_bw_filename, sprite_tilesheet_offset_bytes, sprite_dims_byte, sprite_bw_palette_bytes)

            # Write pokemon name to the generation name list
            append_sprite_name_to_list(sprite_list_filename, pokemon_sub_number)
            num_sprites += 1
            tilesheet_offset += len(pokemon_tiles)

        if (int(pokemon_number)) == LAST_NUMBER_IN_EACH_GENERATION[current_gen]:
            tiles_per_generation.append(tilesheet_offset)
            tilesheet_offset = 0
            sprites_per_generation.append(num_sprites)
            num_sprites = 0
            
            current_gen += 1
            print(f"Generation {current_gen} complete!")
            if current_gen == 6:
                break
            
            generation_directory = os.path.join(output_directory, f"Generation_{current_gen+1}")
            os.makedirs(generation_directory)

            sprite_tilesheet_filename = os.path.join(generation_directory, "SpriteTilesheet.bin")
            open(sprite_tilesheet_filename, "wb").close()
            sprite_tilesheet_bw_filename = os.path.join(generation_directory, "SpriteTilesheet~bw.bin")
            open(sprite_tilesheet_bw_filename, "wb").close()
            sprite_data_filename = os.path.join(generation_directory, "SpriteData.bin")
            open(sprite_data_filename, "wb").close()
            sprite_data_bw_filename = os.path.join(generation_directory, "SpriteData~bw.bin")
            open(sprite_data_bw_filename, "wb").close()
            sprite_list_filename = os.path.join(generation_directory, "SpriteList.txt")
            open(sprite_list_filename, "w").close()
            sprite_image_directory = os.path.join(generation_directory, f"SpriteImages")
            os.makedirs(sprite_image_directory)
            sprite_image_bw_directory = os.path.join(generation_directory, f"SpriteImages~bw")
            os.makedirs(sprite_image_bw_directory)
            
            # For each sprite: 
            # - Find palette
            # - Palette image
            # - Convert to tilesheet
            # - Append to mega tilesheet
            # - Keep track of:
            #   - How big the sprite is in tiles (w, h)
            #   - byte offset on the sheet
            #   - The palette (store all 16 bytes)
            # - Add name to a mega list
            
            # pokemon_output_sub_directory = os.path.join(pokemon_output_directory, os.path.basename(os.path.dirname(pokemon_sub_directory)))
            # os.makedirs(pokemon_output_sub_directory)
    
    # for dims in sorted(size_count.keys(), key=sum):
    #     print(f"{(dims[0]//TILE_WIDTH, dims[1]//TILE_HEIGHT)}: {size_count[dims]}")
    

    misc_data_filename = os.path.join(output_directory, "MiscData.txt")
    with open(misc_data_filename, "w") as f_out:
        for i in range(len(tiles_per_generation)):
            num_tiles = tiles_per_generation[i]
            tile_bytes = num_tiles * 32
            num_sprites = sprites_per_generation[i]
            sprite_bytes = num_sprites * 19
            total_bytes = tile_bytes + sprite_bytes
            average_per_sprite = math.ceil(total_bytes / num_sprites)
            f_out.write(f"Gen {i+1}:\n")
            f_out.write(f"\t{num_tiles} tiles ({tile_bytes} bytes)\n")
            f_out.write(f"\t{num_sprites} sprites ({sprite_bytes} bytes)\n")
            f_out.write(f"\tTotal size: {total_bytes} bytes (Average {average_per_sprite} bytes per sprite)\n")
            
    print(f"Conversion complete!")
    "\d{3}(_[1-9]+\d*)*\/"
    # Up until now we've done every sprite, but now we can filter out:
    # "*_0" sprites from 493 and under
    # "###s" sprites
    # Really just want anything that matches '###_X' where X > 0


if __name__ == "__main__":
    function_type = sys.argv[1]
    if function_type == "extract":
        print(f"Extracting from {sys.argv[2]} to {sys.argv[3]}")
        extract_sprites(sys.argv[2], sys.argv[3])
    elif function_type == "crop":
        print(f"Cropping from {sys.argv[2]} to {sys.argv[3]}")
        crop_sprites(sys.argv[2], sys.argv[3])
    elif function_type == "filter":
        print(f"Filtering from {sys.argv[2]} to {sys.argv[3]}")
        # filter_sprites(sys.argv[2], sys.argv[3])
    elif function_type == "convert":
        print(f"Converting from {sys.argv[2]} to {sys.argv[3]}")
        convert_sprites(sys.argv[2], sys.argv[3])