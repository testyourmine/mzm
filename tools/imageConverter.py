from array import array
from io import BufferedReader, BytesIO
import shutil
import os
from math import ceil
import paletteConverter as pal
import compress as comp
from PIL import Image, ImageDraw
from pathlib import Path

rom: BufferedReader = open("../mzm_us_baserom.gba", "rb")

subDirs: array = []

# Get the file path of the desired file name
def GetFile(filename: str):
    for root, dirs, files in os.walk(".."):
        if filename in files:
            filepath = os.path.join(root, filename)
            return filepath
    return ""

# Get all file paths of the desired file extension
def GetAllFileExtensions(fileextension: str):
    for root, dirs, files in os.walk(".."):
        for file in files:
            if file.endswith(fileextension):
                file_path = os.path.join(root, file)
                subDirs.append(file_path)

# Convert the GBA GFX file to PNG file
def ConvertGbaGfxToPng(
    sprite_file: BufferedReader, # The sprite data to read from
    sprite_array: array, # The sprite data to write to
    palette_array: array, # The palette data to read from
    palette_offset: int, # The palette number to use
    png_mode: int # 0: Truecolor, 1: Indexed
):
    while sprite_file.peek():
        byte = int.from_bytes(sprite_file.read(1), "little")

        # 4 BPP, so each 4 bits (nybble) indexes into the palette
        low_index = (byte >> 0) & 0xF
        high_index = (byte >> 4) & 0xF
        
        # If PNG is Truecolor, then each pixel is a direct RGB value
        if png_mode == 0:
            # Get the colors from the low and high index
            low_color = palette_array[low_index + palette_offset*16]
            high_color = palette_array[high_index + palette_offset*16]

            # Little endian, so low then high
            sprite_array.append(low_color)
            sprite_array.append(high_color)
        
        # If PNG is Indexed, then each pixel is an index into the palette
        elif png_mode == 1:
            # Little endian, so low then high
            sprite_array.append(low_index)
            sprite_array.append(high_index)

# Create PNG image of sprite
def CreateSpritePng(
    png_mode: int, # 0: Truecolor, 1: Indexed
    sprite_array: array, # The data for the sprite
    palette_array: array, # The data for the palette
    sprites_per_row: int, # The number of sprites per row
    scale: int, # The amount to scale the image by
    output_image: str, # The file name/directory to output the image
):
    # Each sprite is 8x8, laid out horizontally
    sprite_width = 8
    sprite_height = 8
    sprite_size = sprite_width * sprite_height

    # Number of rows
    num_rows = ceil(len(sprite_array) / (sprite_size * sprites_per_row))

    # Create a new image that is sprites_per_row sprites wide and num_rows sprites tall
    width = sprite_width * sprites_per_row
    height = sprite_height * num_rows
    image = 0
    # If PNG is Truecolor, then each pixel is a direct RGB value
    if png_mode == 0:
        image = Image.new("RGB", (width * scale, height * scale))
    # If PNG is Indexed, then each pixel is an index into the palette
    elif png_mode == 1:
        image = Image.new("P", (width * scale, height * scale))
        image.putpalette(palette_array)
    draw = ImageDraw.Draw(image)

    # Size of each pixel and offset for laying out sprites
    pixel_width = 1 * scale
    pixel_height = 1 * scale
    offset_x = 0
    offset_y = 0
    rgb = 0

    # Draw each color in the palette
    for i, color in enumerate(sprite_array):
        #print(hex(color))
        if png_mode == 0:
            # Get the RGB values as a tuple, since that's what it expects
            r = (color >> 16) & 0xFF
            g = (color >> 8) & 0xFF
            b = color & 0xFF
            rgb = (r, g, b)
        elif png_mode == 1:
            rgb = color

        # After each 8x8 sprite, lay the next sprite horizontal to it
        if i > 0 and i % sprite_size == 0:
            offset_x += sprite_width * pixel_width
        
        # After sprites_per_row sprites, go to next row
        if i > 0 and i % (sprite_size * sprites_per_row) == 0:
            offset_x = 0
            offset_y += sprite_height * pixel_height

        # Get the coordinates of square, in terms of (x0, y0) and (x1, y1)
        x0 = (i % sprite_width) * pixel_width + offset_x
        x1 = x0 + pixel_width
        y0 = ((i // sprite_width) % sprite_height) * pixel_height + offset_y
        y1 = y0 + pixel_height

        #print(f'{x0},{y0} {x1},{y1}')
        draw.rectangle([x0, y0, x1, y1], fill=rgb)

    # Save the image
    image.save(output_image)

def DecompressImage(sprite_file: BufferedReader) -> tuple[BufferedReader, int]:
    content = sprite_file.read()
    raw, size = comp.decomp_lz77(content, 0)
    sprite_file.close()
    return BufferedReader(BytesIO(raw)), size

def ImageConverter(
    input_sprites: list[str], # The file name/directory of the GFX to input
    input_palette: str, # The file name/directory of the palette the GFX uses
    palette_offset: int, # The palette number to use
    png_flag: int, # 0: No PNG, 1: Output PNG
    png_mode: int, # 0: Truecolor, 1: Indexed
    sprites_per_row: int, # The number of sprites per row
    scale: int, # The amount to scale the image by
    output_image: str, # The file name/directory to output the image
) -> array:
    palette_array = pal.PaletteConverter(input_palette, 0, png_mode, "")
    sprite_array = []

    for input_sprite in input_sprites:
        #sprite_file_path = GetFile(input_sprite)
        sprite_file_path = input_sprite
        if sprite_file_path == "":
            print(f'File not found: {input_sprite}')
            continue
        sprite_file: BufferedReader = open(sprite_file_path, "rb")

        if sprite_file_path.endswith(".lz"):
            sprite_file, size = DecompressImage(sprite_file)

        ConvertGbaGfxToPng(sprite_file, sprite_array, palette_array, palette_offset, png_mode)
        sprite_file.close()

    if png_flag == 1:
        CreateSpritePng(png_mode, sprite_array, palette_array, sprites_per_row, scale, output_image)

    return sprite_array

ImageConverter(
    input_sprites=["../data/sprites/Multiviola.gfx.lz"],
    input_palette="../data/sprites/Multiviola.pal",
    palette_offset=0,
    png_flag=1,
    png_mode=0,
    sprites_per_row=32,
    scale=2,
    output_image="sprite.png"
)

def ConvertAllImages():
    db: BufferedReader = open("../image_database.txt", "r")

    line: str = db.readline()
    while line != '':
        # Formatted as follows : image_name;palette_name;palette_offset;sprites_per_row
        # The symbol # can be used as the first character of a line to make the extractor ignore it
        if line[0] != '\n' and line[0] != '#':
            info: list[str] = line.split(";")
            image_name: str = info[0]#.split("/")[-1]
            palette_name: str = info[1]#.split("/")[-1]
            palette_offset: int = int(info[2])
            sprites_per_row: int = int(info[3])

            input_sprites = ["../data/" + image_name]
            input_palette = "../data/" + palette_name
            png_flag = 1
            png_mode = 1
            scale = 2
            output_image = image_name.split("/")[-1].split(".")[0] + ".png"
            print(f'Image:{image_name}, Palette:{palette_name}, Offset:{palette_offset}, Rows:{sprites_per_row}')
            ImageConverter(input_sprites, input_palette, palette_offset, png_flag, png_mode, sprites_per_row, scale, output_image)
            
        line = db.readline()

def TempConvertDatabaseToImageDatabase():
    db: BufferedReader = open("../database.txt", "r")

    line: str = db.readline()
    while line != '':
        # Formatted as follows : image_name;palette_name;palette_offset;sprites_per_row
        # The symbol # can be used as the first character of a line to make the extractor ignore it
        if line[0] != '\n' and line[0] != '#':
            info: array = line.split(";")
            image_name: str = info[0]
            if image_name.endswith(".lz") or image_name.endswith(".gfx"):
                palette_name: str = Path(image_name.rstrip(".lz")).with_suffix(".pal")
                palette_offset = 0
                sprites_per_row = 32
                sprite_size = int(info[1])
                if image_name.endswith(".lz"):
                    input_sprite = image_name.split("/")[-1]
                    sprite_file_path = GetFile(input_sprite)
                    sprite_file: BufferedReader = open(sprite_file_path, "rb")
                    content = sprite_file.read()
                    e, sprite_size = comp.decomp_lz77(content, 0)
                    sprite_file.close()
                sprites_per_row = sprite_size // 64
                if sprite_size // 64 == 0:
                    sprites_per_row = ceil(sprite_size / 8)

                print(f'{image_name};{palette_name};{palette_offset};{sprites_per_row}')
        
        else:
            print(line, end="")
            
        line = db.readline()

#TempConvertDatabaseToImageDatabase()
#ConvertAllImages()