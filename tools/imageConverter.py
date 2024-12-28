from array import array
from io import BufferedReader, BytesIO
import shutil
import os
import paletteConverter as pal
import compress as comp
from PIL import Image, ImageDraw

rom: BufferedReader = open("../mzm_us_baserom.gba", "rb")

subDirs: array = []

# Get the file path of the desired file name
def GetFile(filename: str):
    for root, dirs, files in os.walk(".."):
        if filename in files:
            filepath = os.path.join(root, filename)
            return filepath

# Get all file paths of the desired file extension
def GetAllFileExtensions(fileextension: str):
    for root, dirs, files in os.walk(".."):
        for file in files:
            if file.endswith(fileextension):
                file_path = os.path.join(root, file)
                subDirs.append(file_path)

# Convert the GBA GFX file to a PNG format
def ConvertGbaGfxToPng(sprite_file: BufferedReader, sprite_array: array, palette_array: array, palette_offset = 0):
    while sprite_file.peek():
        byte = int.from_bytes(sprite_file.read(1), "little")

        # 4 BPP, so each 4 bits indexes into the palette
        low_nybble = (byte >> 0) & 0xF
        high_nybble = (byte >> 4) & 0xF
        
        # Get the color index for the high and low 4 bits (nybble)
        low_indexed_color = palette_array[low_nybble + palette_offset*16]
        high_indexed_color = palette_array[high_nybble + palette_offset*16]

        # Little endian, so low then high
        sprite_array.append(low_indexed_color)
        sprite_array.append(high_indexed_color)

# Create PNG image of sprite
def CreateSprPng_Rows(
    sprite_array: array, # The data for the sprite
    scale: int, # The amount to scale the image by
    output_image: str, # The file name/directory to output the image
):
    # Each sprite is 8x8, laid out horizontally
    sprite_width = 8
    sprite_height = 8
    sprite_size = sprite_width * sprite_height

    # 32 sprites per row and number of rows
    sprites_per_row = 32
    num_rows = int(len(sprite_array) / (sprite_size * sprites_per_row)) #16

    # Create a new image that is 32 sprites wide and 16 sprites tall
    width = sprite_width * sprites_per_row
    height = sprite_height * num_rows
    image = Image.new("RGB", (width * scale, height * scale))
    draw = ImageDraw.Draw(image)

    # Size of each pixel and offset for laying out sprites
    box_width = 1 * scale
    box_height = 1 * scale
    offset_x = 0
    offset_y = 0

    # Draw each color in the palette
    for i, color in enumerate(sprite_array):
        #print(hex(color))
        # Get the RGB values as a tuple, since that's what it expects
        r = (color >> 16) & 0xFF
        g = (color >> 8) & 0xFF
        b = color & 0xFF
        rgb = (r, g, b)

        # After each 8x8 sprite, lay the next sprite horizontal to it
        if i > 0 and i % sprite_size == 0:
            offset_x += sprite_width * box_width
        
        # After 32 sprites, go back to next row
        if i > 0 and i % (sprite_size * sprites_per_row) == 0:
            offset_x = 0
            offset_y += sprite_height * box_height

        # Get the coordinates of square, in terms of (x0, y0) and (x1, y1)
        x0 = (i % sprite_width) * box_width + offset_x
        x1 = x0 + box_width
        y0 = ((i // sprite_width) % sprite_height) * box_height + offset_y
        y1 = y0 + box_height

        #print(f'{x0},{y0} {x1},{y1}')
        draw.rectangle([x0, y0, x1, y1], fill=rgb)

    # Save the image
    image.save(output_image)

def DecompressImage(sprite_file: BufferedReader) -> BufferedReader:
    content = sprite_file.read()
    raw, size = comp.decomp_lz77(content, 0)
    sprite_file.close()
    return BufferedReader(BytesIO(raw))

def ImageConverter(
    input_sprite: str, # The file name/directory of the GFX to input
    input_palette: str, # The file name/directory of the palette the GFX uses
    png_flag: int, # 0: No PNG, 1: Output PNG
    scale: int, # The amount to scale the image by
    output_image: str, # The file name/directory to output the image
) -> array:
    palette_array = pal.PaletteConverter(input_palette, 0, "")

    sprite_file_path = GetFile(input_sprite)
    sprite_file: BufferedReader = open(sprite_file_path, "rb")

    if sprite_file_path.endswith(".lz"):
        sprite_file = DecompressImage(sprite_file)

    sprite_array = []
    ConvertGbaGfxToPng(sprite_file, sprite_array, palette_array)

    if png_flag == 1:
        CreateSprPng_Rows(sprite_array, scale, output_image)

    sprite_file.close()
    return sprite_array

#ImageConverter("Ridley.gfx.lz", "Ridley.pal", 1, 4, "sprite.png")