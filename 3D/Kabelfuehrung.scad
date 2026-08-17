$fn=60;
color("SlateGray")

difference(){
cylinder(h = 6, d=10, center = true);
cylinder(h = 9, d=3, center = true);

translate(v = [-0, -0, -4.5])
cube(size = [1.5,8,10]);
}

color("SlateGray")
translate(v = [-5, -3, -3])
cube(size = [1,6,6]);


