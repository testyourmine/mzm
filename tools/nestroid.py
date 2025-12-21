import argparse
from typing import Tuple


NESTROID_OFFSET_ADDR = 0x7D814C
"""Stores the offset that's added to this address to get the ROM address."""
NESTROID_ROM_ADDR = 0x7DCF60
"""Address of the LZ compressed nestroid ROM data."""
# Comp end: 0x7F3397
# Comp size: 0x16437
NESTROID_ROM_SIZE = 0x20000
"""Decompressed size of the nestroid ROM."""
FREESPACE_ADDR = 0x7F7734
"""Freespace address where a new ROM can be written."""

MIN_MATCH_SIZE = 2
MIN_WINDOW_SIZE = 1

MAX_MATCH_SIZE = (1 << 8) - 1 + 0x10 + MIN_MATCH_SIZE
MAX_WINDOW_SIZE = (1 << 12) - 1 + MIN_WINDOW_SIZE


def decomp_lz(src: bytes, idx: int, size: int) -> Tuple[bytes, int]:
    output = bytearray(size)

    start = idx
    dst = 0

    while (True):
        cflag = src[idx]
        idx += 1

        for _ in range(8):
            if (cflag & 0x80) != 0:
                # Uncompressed
                output[dst] = src[idx]
                idx += 1
                dst += 1
            else:
                # Compressed
                amount_to_copy = (src[idx] >> 4)
                window = ((src[idx] & 0xF) << 8) + src[idx + 1] + 1
                idx += 2
                if amount_to_copy == 0:
                    amount_to_copy = 0x10 + src[idx]
                    idx += 1
                amount_to_copy += MIN_MATCH_SIZE

                for _ in range(amount_to_copy):
                    output[dst] = output[dst - window]
                    dst += 1

            if dst >= size:
                if dst > size:
                    raise ValueError("Too many bytes copied at end")
                comp_size = idx - start
                return bytes(output), comp_size
            cflag <<= 1


def comp_lz(input: bytes) -> bytes:
    # Assumes input stream starts at 0
    length = len(input)
    idx = 0
    longest_matches = find_longest_matches(input)

    output = bytearray()

    while idx < length:
        # Get index of new compression flag
        flag = len(output)
        output.append(0)

        for i in range(8):
            # Find longest match at current position
            _match = longest_matches.get(idx)
            if _match is not None:
                # Compressed
                match_len, match_idx = _match
                match_offset = idx - match_idx - MIN_WINDOW_SIZE
                if match_len - MIN_MATCH_SIZE < 0x10:
                    output.append(((match_len - MIN_MATCH_SIZE) << 4) | (match_offset >> 8))
                    output.append(match_offset & 0xFF)
                else:
                    output.append(match_offset >> 8)
                    output.append(match_offset & 0xFF)
                    output.append(match_len - 0x10 - MIN_MATCH_SIZE)
                idx += match_len
            else:
                # Uncompressed
                output.append(input[idx])
                idx += 1
                output[flag] |= 0x80 >> i

            # Check if at end
            if idx >= length:
                return bytes(output)
    
    raise Exception("LZ77 compression error")


def find_longest_matches(input: bytes) -> dict[int, tuple[int, int]]:
    length = len(input)
    triplets: dict[int, list[int]] = {}
    longest_matches: dict[int, tuple[int, int]] = {}

    for i in range(length - 2):
        # Get triplet at current position
        triplet = input[i] | (input[i + 1] << 8) | (input[i + 2] << 16)

        # Check if triplet has no match
        indexes = triplets.get(triplet)
        if indexes is None:
            triplets[triplet] = [i]
            continue

        window_start = max(i - MAX_WINDOW_SIZE, 0)
        # NOTE: Using a smaller MAX_MATCH_SIZE until this function is optimized
        max_size = min(32, length - i)
        longest_len = 0
        longest_idx = -1

        # Skip first index if one byte behind current position
        j = len(indexes) - 1
        if indexes[j] >= i - 1:
            j -= 1

        # Try each index to find the longest match
        while j >= 0:
            idx = indexes[j]
            # Stop if past window
            if idx < window_start:
                break

            # Find length of match
            match_len = 3
            while match_len < max_size:
                if input[idx + match_len] != input[i + match_len]:
                    break
                match_len += 1
            
            # Update longest match
            if match_len > longest_len:
                longest_len = match_len
                longest_idx = idx

                # Stop looking if max size
                if longest_len == max_size:
                    break
            
            j -= 1

        indexes.append(i)
        if longest_len >= 3:
            longest_matches[i] = (longest_len, longest_idx)

    return longest_matches


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("input_path", type=str, help="Path to input")
    parser.add_argument("output_path", type=str, help="Path to output")

    args = parser.parse_args()
    in_path = args.input_path
    out_path = args.output_path

    # Open the input file
    with open(in_path, "rb") as f:
        in_data = bytearray(f.read())
    
    # Compress the file
    comp_data = comp_lz(in_data)

    with open(out_path, "wb") as f:
        f.write(comp_data)

    # parser = argparse.ArgumentParser()
    # parser.add_argument("zm_path", type=str, help="Path to a Zero Mission ROM")
    # parser.add_argument("nes_path", type=str, help="Path to an NES ROM to insert")
    # parser.add_argument("output_path", type=str, help="Path where output ROM should be written")

    # args = parser.parse_args()
    # zm_path = args.zm_path
    # nes_path = args.nes_path
    # out_path = args.output_path

    # Open the ZM rom
    # with open(zm_path, "rb") as f:
    #     zm_data = bytearray(f.read())
    
    # TODO: make sure ROM is valid

    # # Open the NES rom
    # with open(nes_path, "rb") as f:
    #     nes_data = bytes(f.read())

    # # Check length and mapper
    # assert len(nes_data) == 0x20010, "Invalid NES ROM size. Must be 128 KB."
    # mapper = (nes_data[6] >> 4) | (nes_data[7] & 0xF0)
    # assert mapper == 1, "Invalid NES mapper. Must be MMC1."

    # # Compress the NES rom
    # nes_data = nes_data[0x10 :]
    # comp_data = comp_lz(nes_data)

    # t, _ = decomp_lz(comp_data, 0, NESTROID_ROM_SIZE)
    # assert t == nes_data

    # # Write the new offset so that rom data is expected at freespace
    # offset = (FREESPACE_ADDR - NESTROID_OFFSET_ADDR) // 4
    # zm_data[NESTROID_OFFSET_ADDR + 2] = offset & 0xFF
    # zm_data[NESTROID_OFFSET_ADDR + 3] = offset >> 8

    # # Copy rom data to freespace
    # end = FREESPACE_ADDR + len(comp_data)
    # zm_data[FREESPACE_ADDR : end] = comp_data

    # # nop call to LZ77 decomp
    # zm_data[0x7DBF26] = 0xC0
    # zm_data[0x7DBF27] = 0x46

    # # Unlock nestroid from start
    # # 0x7A02C = 0x7A11A
    # zm_data[0x7A02C] = 0x1A
    # zm_data[0x7A02D] = 0xA1
    # zm_data[0x7A02E] = 0x07
    # zm_data[0x7A02F] = 0x08

    # with open(out_path, "wb") as f:
    #     f.write(zm_data)
