from array import array
from io import BufferedReader
import shutil
import os
from PIL import Image, ImageDraw

rom: BufferedReader = open("../mzm_us_baserom.gba", "rb")

# GBA format: BGR555, 5 bits for each, 1 MSB unused
# PNG format: RGB888, 8 bits for each, 8 MSB unused
def Bgr555toRgb888(bgr555: int, png_mode: int):
    red555 = (bgr555 >> 0) & 0x1F
    green555 = (bgr555 >> 5) & 0x1F
    blue555 = (bgr555 >> 10) & 0x1F

    # Put the 5 bits into the top 8 bits, and propagate the top 3 bits down
    # Helps create a better color conversion
    red888 = (red555 << 3) | (red555 >> 2)
    green888 = (green555 << 3) | (green555 >> 2)
    blue888 = (blue555 << 3) | (blue555 >> 2)

    rgb888 = 0
    if png_mode == 0:
        rgb888 = (red888 << 16) | (green888 << 8) | (blue888)
    elif png_mode == 1:
        rgb888 = (red888, green888, blue888)
    return rgb888

# PNG format: RGB888, 8 bits for each, 8 MSB unused
# GBA format: BGR555, 5 bits for each, 1 MSB unused
def Rgb888toBgr555(rgb888: int, png_mode: int):
    blue888 = (rgb888 >> 0) & 0xFF
    green888 = (rgb888 >> 8) & 0xFF
    red888 = (rgb888 >> 16) & 0xFF

    # Take the top 5 bits from the 8 bits
    red555 = (red888 >> 3)
    green555 = (green888 >> 3)
    blue555 = (blue888 >> 3)

    bgr555 = 0
    if png_mode == 0:
        bgr555 = (blue555 << 10) | (green555 << 5) | (red555 << 0)
    elif png_mode == 1:
        bgr555 = (blue555, green555, red555)
    return bgr555

# Convert the GBA palette to a PNG palette
def ConvertGbaPalToPngPal(
    palette_file: BufferedReader, # The palette data to read from
    palette_array: array, # The palette data to write to
    png_mode: int, # 0: Truecolor, 1: Indexed
):
    while palette_file.peek():
        bgr555 = int.from_bytes(palette_file.read(2), "little")
        rgb888 = Bgr555toRgb888(bgr555, png_mode)
        if png_mode == 0:
            palette_array.append(rgb888)
        elif png_mode == 1:
            palette_array.extend(rgb888)
        #print(hex(palette[-1]))

# Create PNG image of palette, where each row is 16 colors
def CreatePalPng(
    png_mode: int, # 0: Truecolor, 1: Indexed
    palette_array: array, # The data for the palette
    output_image: str, # The file name/directory to output the image
    palette_length: int, # The number of colors per row
):
    # Create a new image
    scale = 30
    width = palette_length
    height = int(len(palette_array) / palette_length)
    image = 0
    # If PNG is Truecolor, then each pixel is a direct RGB value
    if png_mode == 0:
        image = Image.new("RGB", (width * scale, height * scale))
    # If PNG is Indexed, then each pixel is an index into the palette
    elif png_mode == 1:
        image = Image.new("P", (width * scale, height * scale))
        image.putpalette(palette_array)
    draw = ImageDraw.Draw(image)

    # Size of each pixel
    box_width = 1 * scale
    box_height = 1 * scale
    rgb = 0

    # Draw each color in the palette
    for i, color in enumerate(palette_array):
        #print(hex(color))
        if png_mode == 0:
            # Get the RGB values as a tuple, since that's what it expects
            r = (color >> 16) & 0xFF
            g = (color >> 8) & 0xFF
            b = (color >> 0) & 0xFF
            rgb = (r, g, b)
        elif png_mode == 1:
            rgb = i

        # Get the coordinates of square, in terms of (x0, y0) and (x1, y1)
        x0 = (i % palette_length) * box_width
        x1 = x0 + box_width
        y0 = (i // palette_length) * box_height
        y1 = y0 + box_height

        #print(f'{x0},{y0} {x1},{y1}')
        draw.rectangle([x0, y0, x1, y1], fill=rgb)

    # Save the image
    image.save(output_image)

def PaletteConverter(
    input_palette: str, # The file name/directory of the palette to input
    png_flag: int, # 0: No PNG, 1: One row, 2: Multiple rows
    png_mode: int, # 0: Truecolor, 1: Indexed
    output_image: str, # The file name/directory to output the image
    colors_per_row = 16, # Number of colors per row
) -> array:
    #pal_file_path = GetFile(input_palette)
    palette_file_path = input_palette
    if palette_file_path == "":
        print(f'File not found: {input_palette}')
        return []
    palette_file: BufferedReader = open(palette_file_path, "rb")

    palette_array = []
    ConvertGbaPalToPngPal(palette_file, palette_array, png_mode)

    if png_flag != 0:
        palette_length = 0
        if png_flag == 1:
            palette_length = len(palette_array)
        elif png_flag == 2:
            palette_length = colors_per_row
        CreatePalPng(png_mode, palette_array, output_image, palette_length)
    
    palette_file.close()
    return palette_array

PaletteConverter(
    input_palette="../data/sprites/Multiviola.pal",
    png_flag=2,
    png_mode=1,
    output_image="palette.png",
)
