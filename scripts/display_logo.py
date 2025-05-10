import argparse
from typing import List, Dict, Optional, Tuple

# Constants for Game Boy tile data
BYTES_PER_TILE: int = 16
TILE_WIDTH_PX: int = 8
TILE_HEIGHT_PX: int = 8

# Constants for Nintendo Logo in cartridge header
LOGO_START_ADDRESS: int = 0x0104
LOGO_END_ADDRESS: int = 0x0133  # Inclusive
LOGO_DATA_SIZE: int = LOGO_END_ADDRESS - LOGO_START_ADDRESS + 1  # 48 bytes

# Pixel characters (0: White, 1: Light Gray, 2: Dark Gray, 3: Black)
PIXEL_CHARS: Dict[int, str] = {
    0: ' ',  # White
    1: '░',  # Light Gray
    2: '▓',  # Dark Gray
    3: '█'   # Black
}

def read_rom_file(filepath: str) -> Optional[bytes]:
    """Reads the Game Boy ROM file."""
    try:
        with open(filepath, 'rb') as f:
            rom_data: bytes = f.read()
        return rom_data
    except FileNotFoundError:
        print(f"Error: ROM file not found at '{filepath}'")
        return None
    except Exception as e:
        print(f"Error reading ROM file: {e}")
        return None

def extract_logo_tile_data(rom_data: bytes) -> Optional[bytes]:
    """Extracts the Nintendo logo tile data from the ROM."""
    if not rom_data or len(rom_data) < LOGO_END_ADDRESS + 1:
        print(f"Error: ROM is too small or empty. Expected at least {LOGO_END_ADDRESS + 1} bytes, got {len(rom_data) if rom_data else 0}.")
        return None
    
    logo_data: bytes = rom_data[LOGO_START_ADDRESS : LOGO_END_ADDRESS + 1]
    
    # This check is mostly for sanity, as slicing a sufficiently large rom_data
    # with these constants should always yield LOGO_DATA_SIZE bytes.
    if len(logo_data) != LOGO_DATA_SIZE:
        print(f"Error: Extracted logo data size is incorrect. Expected {LOGO_DATA_SIZE}, got {len(logo_data)}.")
        return None
    return logo_data

def render_tile(tile_data_bytes: bytes) -> None:
    """Renders a single 8x8 tile from its 16 bytes of data."""
    if len(tile_data_bytes) != BYTES_PER_TILE:
        print(f"Error: Invalid tile data length. Expected {BYTES_PER_TILE} bytes, got {len(tile_data_bytes)}.")
        return
    
    for y in range(TILE_HEIGHT_PX):
        # Each row of 8 pixels is represented by two bytes in Game Boy tile format.
        # Byte 1 contains the LSBs for the 8 pixels in the row.
        # Byte 2 contains the MSBs for the 8 pixels in the row.
        byte1: int = tile_data_bytes[y * 2]
        byte2: int = tile_data_bytes[y * 2 + 1]
        
        row_str: str = ""
        for x in range(TILE_WIDTH_PX):
            # Pixels are stored from left to right.
            # Bit 7 of byte1/byte2 corresponds to the leftmost pixel (pixel 0).
            # Bit 0 of byte1/byte2 corresponds to the rightmost pixel (pixel 7).
            bit_pos: int = 7 - x  # Convert pixel index (0-7) to bit position (7-0)
            
            lsb: int = (byte1 >> bit_pos) & 1
            msb: int = (byte2 >> bit_pos) & 1
            
            # Combine LSB and MSB to get the 2-bit color value (00, 01, 10, 11).
            # MSB is the most significant bit of the color.
            color_value: int = (msb << 1) | lsb
            row_str += PIXEL_CHARS.get(color_value, '?') # Default to '?' if color_value is unexpected
        print(row_str)

def main() -> None:
    parser = argparse.ArgumentParser(
        description="Reads a Game Boy ROM and prints the Nintendo logo tiles that appear during boot."
    )
    parser.add_argument("rom_path", help="Path to the Game Boy ROM file.")
    args = parser.parse_args()

    rom_data: Optional[bytes] = read_rom_file(args.rom_path)
    if not rom_data:
        return

    logo_tile_data: Optional[bytes] = extract_logo_tile_data(rom_data)
    if not logo_tile_data:
        return

    num_tiles: int = len(logo_tile_data) // BYTES_PER_TILE
    print(f"Found {num_tiles} tiles for the Nintendo logo (total {len(logo_tile_data)} bytes from address 0x{LOGO_START_ADDRESS:04X}).\n")

    for i in range(num_tiles):
        tile_start_index: int = i * BYTES_PER_TILE
        current_tile_data: bytes = logo_tile_data[tile_start_index : tile_start_index + BYTES_PER_TILE]
        
        print(f"Tile #{i + 1}:")
        render_tile(current_tile_data)
        if i < num_tiles - 1: # Print separator for all but the last tile
            print("-" * TILE_WIDTH_PX) 

if __name__ == "__main__":
    main()