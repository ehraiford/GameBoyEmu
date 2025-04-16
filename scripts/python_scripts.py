
def rip_bytes_from_binary(path_to_binary: str):
    bytes_per_line=16
    with open(path_to_binary, 'rb') as file:
        data = file.read()
        hex_pairs = [f"0x{b:02x}" for b in data]
        for i in range(0, len(hex_pairs), bytes_per_line):
            line = ", ".join(hex_pairs[i:i + bytes_per_line])
            print(f"{line},")



if __name__ == "__main__":
    rip_bytes_from_binary("../roms/bootix_dmg.bin")