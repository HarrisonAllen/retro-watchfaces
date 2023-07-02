# GBA Style watchface generator

Have an idea you *really* want to do, but don't know how to do any of the Python or Pebble sdk stuff? If you follow steps 1-3 then reach out to me (harrisonallen555@gmail.com) with a zip of your project, I may be able to generate the watchface for you (no promises, it'll depend on my availability).

**What this does:**
* Generates a GBA style pebble project that does the following:
    * Loads in a random background group (background, foreground, numbers) when starting
    * A random sprite walks on screen
    * Every second or minute, the sprite will take a step and the backgrounds will scroll
    * Every minute or hour, the sprite will swap out with a different one
* Generates a project compatible with Basalt (Pebble Time, Pebble Time Steel), Chalk (Pebble Time Round), and Diorite (Pebble 2 SE, Pebble 2 HR)

**What this doesn't do:**
* Generate a .pbw that you can install on a watch, you'll have to do that yourself
* Generate a project compatible with Aplite (Pebble, Pebble Steel)

# Project file structure
```
├─ README.md - This 
├─ WatchfaceGenerator.py - Run this to generate a watchface
├─ Templates.py - A helper script for WatchfaceGenerator.py
├─ template-watchface - The project template that WatchfaceGenerator.py uses
├─ example-project - An example of how you should set up your files for processing
   ├─ Backgrounds - The Background Groups for your watchface
   │  ├─ World0_0 - An example background group
   │  │  ├─ Background.png - The background of this background group, 256 x 184 pixels (32 x 23 tiles)
   │  │  ├─ Foreground.png - The foreground of this background group, 256 x 184 pixels (32 x 23 tiles)
   │  │  └─ Numbers.png - The numbers for time on this background group, each number is 24 x 40 pixels (3 x 5 tiles)
   │  ⋮  
   ├─ Sprites - The Sprite Groups for your watchface
   │  ├─ LuigiBig - An example Sprite Group
   │  │  ├─ Stand.png - An example sprite
   │  ⋮   ⋮
   ├─ config.json - The configuration for the project.
   ├─ background_template.xcf - A template GIMP file for a background.
   ├─ foreground_template.xcf - A template GIMP file for a foreground.
   ├─ numbers_template.xcf - A template GIMP file for the numbers.
   └─ sprite_template.xcf - A template GIMP file for a 16 x 16 pixels (2 x 2 tiles) sprite.
```

# Generating a watchface

## 1. Create your project

Your project must have the following structure:
- Unless otherwise noted, you can change the names of filenames and directories
```
project-name - Can change, any characters allowed
├─ Backgrounds - DO NOT CHANGE THIS NAME
│  ├─ YourBackgroundGroup - Can change, alphanumeric characters and underscores only
│  │  ├─ Background.png - DO NOT CHANGE THIS NAME
│  │  ├─ Foreground.png - DO NOT CHANGE THIS NAME
│  │  └─ Numbers.png - DO NOT CHANGE THIS NAME
│  ⋮  
├─ Sprites - DO NOT CHANGE THIS NAME
│  ├─ LuigiBig - Can change, alphanumeric characters and underscores only
│  │  ├─ Stand.png - Can change, alphanumeric characters and underscores only
│  ⋮   ⋮
└─ config.json - DO NOT CHANGE THIS NAME
```

## 2. Create your assets (backgrounds, foregrounds, numbers, and sprites)

### I highly recommend using GIMP and the templates
If you have [gimp](https://www.gimp.org/), then you can use the template files `background_template.xcf`, `foreground_template.xcf`, `numbers_template.xcf`, and `sprite_template.xcf`.

These files are set up with the correct color space (i.e. only valid Pebble colors) and have the grid set up for tiles (8x8 pixels). You can show the grid by going to `View->Show Grid`. This can be helpful for aligning tiles correctly.

Here's a quick overview of the files:
* `background_template.xcf` - Contains a sample background, with layers representing Pebble screens that you can hide and show to preview what will be visible.
    * The background is 256 x 184 pixels (32 x 23 tiles)
* `foreground_template.xcf` - Contains a sample foreground using transparency, with layers representing Pebble screens that you can hide and show to preview what will be visible.
* `numbers_template.xcf` - Contains all of the numbers. 
    * One number is 24 x 40 pixels (3 x 5 tiles). The available characters are `0`, `1`, `2`, `3`, `4`, `5`, `6`, `7`, `8`, `9`, and `:`.
* `sprite_template.xcf` - An example sprite, this one is 16 x 32 pixels (2 x 4 tiles). 
    * The width and height of a sprite each must be one of the following:
        * 8 pixels (1 tile)
        * 16 pixels (2 tiles)
        * 32 pixels (4 tiles)
        * 64 pixels (8 tiles)
    * Some examples of valid dimensions include:
        * 8 x 16 pixels (1 x 2 tiles)
        * 64 x 64 pixels (8 x 8 tiles)
        * 32 x 16 pixels (4 x 2 tiles)

Save each background group in a directory under `Backgrounds`
* For example, I want to make a background group called `World1_1`
    1. Make a directory in `Backgrounds` called `World1_1`
    2. Export the background file to `Background.png` in the `World1_1` directory
    3. Export the foreground file to `Foreground.png` in the `World1_1` directory
    4. Export the numbers file to `Numbers.png` in the `World1_1` directory

Save each sprite group in a directory under `Sprites`
* For example, I want to make a sprite group called `MarioBig`
    1. Make a directory in `Sprites` called `MarioBig`
    2. Export each sprite image as a `.png` in the `MarioBig` directory
        * E.g. `Stand.png`, `Walk0.png`, etc.


### But you can just use regular images
If you don't want to do that, you can just drop in `.png` files following the correct file structure.

### For best results
* Make sure your images are in the Pebble color space. You can download color palettes for different programs here: https://developer.rebble.io/developer.pebble.com/guides/app-resources/images/index.html#color-palettes
* Make use of tiles. An image is made up of 8 x 8 pixel tiles. For backgrounds, foregrounds, and numbers, the generator will try and pull out matching tiles from your image. Most old retro games already use tiles, so if you're using resources from one of those, just make sure your tiles are aligned.
    * The template images are lined up with tiles, if you need a reference.

## 3. Edit the config
`config.json` contains all of the required parameters for customizing your watchface. Let's go through them together.

* `watchfaceName`
    * The internal name for your watchface. This is all lowercase, no spaces or underscores. Use hyphens to connect words.
* `watchfaceAuthor`
    * Your name!
* `watchfaceDisplayName`
    * The name people will see on the Pebble for your watchface.
* `uuid`
    * A Universally Unique IDentifier. Generate one using https://www.uuidgenerator.net/
* `timeYTileOffset`
    * How many tiles from the top of the background that the time should be placed.
    * For example, increase this number by one to move the time down by one tile (8 pixels)
* `timeYPixelShift`
    * How many pixels downwards the time should be shifted.
    * For example, increase this number by four to move the time down by four pixels
* `spriteBottomY`
    * The pixel position for the bottom of each sprite, measured from the top of the background.
* `backgroundStepSize`
    * How many pixels the background should step during a scroll.
* `foregroundStepSize`
    * How many pixels the foreground should step during a scroll.
* `spriteStepSize`
    * How many pixels a sprite should step when moving on or off the screen.
* `updateEverySecond`
    * Should the watchface update every second?
    * Set to `"true"` to scroll the background every second, and swap out sprites every minute.
    * Set to `"false"` to scroll the background every minute, and swap out sprites every hour.

## 4. Generate a Pebble project

Now that you've created your project, created your images, and filled out the config, you're ready to generate the Pebble project!

### Prerequisites

Here's what I have on my system, you'll probably need it too:
* Python 3.8.5 or higher
* Pillow (`pip install pillow`)

### Running the script

1. Open a terminal in the same directory as `WatchfaceGenerator.py`
2. Run `python3 WatchfaceGenerator.py path/to/project/directory`
    * e.g. for the example project, you'd run `python3 WatchfaceGenerator.py example-project`
3. You should see something along the lines of `Watchface generated!` at the end, and you're done!

## 5. Build and post-process
You can test your new project by going to the output Pebble project directory, and doing the whole `pebble build`, `pebble install` workflow.

If you decide you want to make changes to the generated project, **move it to a new directory**. If you run the generator script again, it will delete the output directory and you'll lose any changes you've made!

### Black and White palettes
The generator will "try" to generate a black and white version of your watchface, but it isn't that great at it. You can manually assign black and white colors by editing `src/c/resources/Palettes.h` in the generated project directory.

The available colors for black and white are:
* black - `0b00` (`GBC_COLOR_BLACK`)
* gray - `0b10` (`GBC_COLOR_GRAY`)
* white - `0b11` (`GBC_COLOR_WHITE`)

For example, some of the Mario sprite palettes end up being mostly gray when converted to black and white, so I would cross-reference `Output/References/MarioBig/Palettes.png` to the generated `src/c/resources/Palettes.h` in the Pebble project, and change the gray colors (0b10) that correspond to red and brown (in the palette image) to black (0b00).

