//+
SetFactory("OpenCASCADE");
 
dx=0.2;

w = 1.0;
h = 1.0;
t = 1.0;
//创建点
Point(1) = {0.0, 0.0, 0.0, dx};
Point(2) = {w, 0.0, 0.0, dx};
Point(3) = {w, h, 0.0, dx};
Point(4) = {0.0, h, 0.0, dx};//+

Point(5) = {0.0, 0.0, t, dx};
Point(6) = {w, 0.0, t, dx};
Point(7) = {w, h, t, dx};
Point(8) = {0.0, h, t, dx};//+



//+
Line(1) = {4, 1};
//+
Line(2) = {4, 8};
//+
Line(3) = {8, 5};
//+
Line(4) = {5, 1};
//+
Line(5) = {5, 6};
//+
Line(6) = {6, 7};
//+
Line(7) = {7, 8};
//+
Line(8) = {4, 3};
//+
Line(9) = {3, 7};
//+
Line(10) = {2, 6};
//+
Line(11) = {2, 3};
//+
Line(12) = {2, 1};
//+
Curve Loop(1) = {1, -4, -3, -2};
//+
Plane Surface(1) = {1};
//+
Curve Loop(2) = {7, 3, 5, 6};
//+
Plane Surface(2) = {2};
//+
Curve Loop(3) = {8, 9, 7, -2};
//+
Plane Surface(3) = {3};
//+
Curve Loop(4) = {9, -6, -10, 11};
//+
Plane Surface(4) = {4};
//+
Curve Loop(5) = {8, -11, 12, -1};
//+
Plane Surface(5) = {5};
//+
Curve Loop(6) = {12, -4, 5, -10};
//+
Plane Surface(6) = {6};
//+
Surface Loop(1) = {3, 5, 4, 2, 1, 6};
//+
Volume(1) = {1};
//+
Physical Surface("left", 1) = {1};
//+
Physical Surface("right", 4) = {4};
//+
Physical Surface("top", 3) = {3};
//+
Physical Surface("bottom", 6) = {6};
//+
Physical Surface("front", 2) = {2};
//+
Physical Surface("back", 5) = {5};
