//+
SetFactory("OpenCASCADE");
dx=0.05;

w = 2.0;
h = 1.0;
//创建点
Point(1) = {0.0, 0.0, 0.0, dx};
Point(2) = {w, 0.0, 0.0, dx};
Point(3) = {w, h, 0.0, dx};
Point(4) = {0.0, h, 0.0, dx};//+
Line(1) = {4, 3};
//+
Line(2) = {3, 2};
//+
Line(3) = {2, 1};
//+
Line(4) = {1, 4};
//+
Circle(5) = {0.5, 0.5, 0, 0.1, 0, 2*Pi};
//+
Curve Loop(1) = {4, 1, 2, 3};
//+
Curve Loop(2) = {1, 2, 3, 4};
//+
Curve Loop(3) = {2, 3, 4, 1};
//+
Curve Loop(4) = {3, 4, 1, 2};
//+
Curve Loop(5) = {5};
//+
Plane Surface(1) = {1, 2, 3, 4, 5};
//+
Physical Curve("inlet", 4) = {4};
//+
Physical Curve("top", 1) = {1};
//+
Physical Curve("bottom", 3) = {3};
//+
Physical Curve("outlet", 2) = {2};
//+
Physical Surface("circle", 5) = {5};

// 圆周围的加密
Field[1] = Distance;
Field[1].EdgesList = {5}; // 对圆边界的编号（即Circle(5)）作用

Field[2] = Threshold;
Field[2].InField = 1;
Field[2].SizeMin = dx / 5; // 圆附近最小网格
Field[2].SizeMax = dx;     // 远处最大网格
Field[2].DistMin = 0.05;   // 小于此距离用最小网格
Field[2].DistMax = 0.2;    // 超过此距离用最大网格

// 启用该场作为背景网格控制
Background Field = 2;

