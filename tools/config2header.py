#!/usr/bin/env python3
with open(".config", encoding="utf-8") as f:
    config = f.read()

for line in config.split("\n"):
    if line.strip():
        if not line.startswith("#"):
            settings = line.split("=")
            name = settings[0]
            option = settings[1]
            print(f"#define {name} {option}")
        else:
            if line[1:]:
                print(f"/*{line[1:]}*/")
