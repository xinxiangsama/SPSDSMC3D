#import "@preview/ilm:1.4.1": *

#set text(lang: "en")
#show: ilm.with(
  title: [SPSDSMC3D 开发手册],
  author: "xinxiangsama",
  date: datetime(year: 2025, month: 05, day: 30),
  abstract: [介绍开发原理、开发思路等],
  figure-index: (enabled: true),
  table-index: (enabled: true),
  listing-index: (enabled: true)
)

= 前处理
- 网格划分
- 网格读取

== 网格划分

== 网格读取

=== 四面体网格

* 体积计算 *
四面体体积计算使用几何向量法:
假设四个顶点坐标为:
$
  A = (x_1, y_1, z_1), \
  B = (x_2, y_2, z_2), \
  C = (x_3, y_3, z_3), \
  D = (x_4, y_4, z_4)
$
则体积公式为:
$
  V = frac(1, 6) * |(B - A) dot ((C - A) times (D - A))|
$

