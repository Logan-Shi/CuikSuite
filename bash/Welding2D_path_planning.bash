# !/bin/bash
cuikatlasrrt ../examples/Welding/Welding2D_limited
cuikplotrrt ../examples/Welding/Welding2D_limited 0 9 18

cuikatlas ../examples/Welding/Welding2D_limited
cuikplotatlas ../examples/Welding/Welding2D_limited 0 9 18

# geomview ../examples/Welding/Welding2D_limited_atlas.gcl ../examples/Welding/Welding2D_limited_rrt.gcl

# cuikplotpath ../examples/Welding/Welding2D_limited 0 9 18
# geomview ../examples/Welding/Welding2D_limited_atlas.gcl ../examples/Welding/Welding2D_limited_path.gcl

cuiksmoothpath ../examples/Welding/Welding2D_limited
cuikplotpath ../examples/Welding/Welding2D_limited ../examples/Welding/Welding2D_limited_path_s 0 9 18
geomview ../examples/Welding/Welding2D_limited_atlas.gcl ../examples/Welding/Welding2D_limited_path_s.gcl

# cuikatlasrrtstar ../examples/Welding/Welding2D_limited
# cuikplotpath ../examples/Welding/Welding2D_limited 0 9 18
# geomview ../examples/Welding/Welding2D_limited_atlas.gcl ../examples/Welding/Welding2D_limited_path.gcl