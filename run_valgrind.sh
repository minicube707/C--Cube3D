#!/bin/bash

for file in maps/bad/*; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        echo "=== Test avec $filename ==="
        valgrind --leak-check=full ./cub3d "$filename"
        echo ""
	echo ""
    fi
done

