# Cub3D

Cub3D is a raycasting project in 42 Project

This project was developed by **fmotte** and **cpollock**.

---

## Installation

### Clone the repository
```bash
git clone https://github.com/minicube707/C--Cube3D.git
```

Complie
```base
make
````

Lauch
```base
./cub3d path_to_the_map
```

### MAP
The program loads the map from the provided path.
A map is considered valid if the player cannot escape outside the map.

### Bonus – Textures & Animations
- If the wall texture paths (NO, SO, EA, WE) are not expanded (.xpm), they are treated as paths to a folder.
- This folder must contain a file named utils.txt.
- utils.txt must list the texture filenames used for wall animations.
- All animated textures must be located in the same folder as utils.txt.

### Door
- Map character: D
- Texture identifier: DO

To test animated textures, you can run:
```base
maps/good/bonus_triangle.cub
```

### Mandatory Controls
Movement:  
- Press **a** (Left)
- Press **w** (Forward)
- Press **s** (Backward)
- Press **d** (Right)
- Press **SHIFT** (Speed)

Camera:
- Press **→** (Left)
- Press **→** (Right)

### Bonus Controls

Map:
- Press **m** (Toggle minimap)

Door:
- Press **space** (Open / close door)

