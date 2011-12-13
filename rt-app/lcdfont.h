#ifndef __FONT_H__
#define __FONT_H__

// Description:	basic fonts for different screen sizes.  8x16
//				is good for VGA and above, 8x8 is good for QVGA
//				landscape (320 x 240), while 5x7 gives the most
//				characters on QVGA portrait mode (240 x 320).
//
//				Note that 8x8 and 5x7 use one byte per font row,
//				but 5x7 uses only the upper 5 bits.
//
//				To lookup, subtract FIRST_CHAR from the character,
//				multiply by FONT_HEIGHT and get the next FONT_WIDTH
//				bytes.  These fonts only support printable ASCII
//				characters 0x20 to 0x7f.
//

#define FIRST_CHAR 0x20
#define LAST_CHAR  0x7F
#define CURSOR_ON  0x7F
#define CURSOR_OFF 0x20

#define FONT_HEIGHT 8
#define FONT_WIDTH  8
#define FONT_STEP	8	// font rows are 8 bytes apart

static unsigned char fb_font_data[LAST_CHAR-FIRST_CHAR+1][FONT_STEP] =
{
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, },	// 0x20
	{ 0x30, 0x78, 0x78, 0x30, 0x30, 0x00, 0x30, 0x00, },	// 0x21  !
	{ 0x6c, 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, },	// 0x22  "
	{ 0x6c, 0x6c, 0xfe, 0x6c, 0xfe, 0x6c, 0x6c, 0x00, },	// 0x23  #
	{ 0x30, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x30, 0x00, },	// 0x24  $
	{ 0x00, 0xc6, 0xcc, 0x18, 0x30, 0x66, 0xc6, 0x00, },	// 0x25  %
	{ 0x38, 0x6c, 0x38, 0x76, 0xdc, 0xcc, 0x76, 0x00, },	// 0x26  &
	{ 0x60, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, },	// 0x27  '
	{ 0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00, },	// 0x28  (
	{ 0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60, 0x00, },	// 0x29  )
	{ 0x00, 0x66, 0x3c, 0xff, 0x3c, 0x66, 0x00, 0x00, },	// 0x2a  *
	{ 0x00, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x00, 0x00, },	// 0x2b  +
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x60, },	// 0x2c  ,
	{ 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, },	// 0x2d  -
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, },	// 0x2e  .
	{ 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, },	// 0x2f  /
	{ 0x7c, 0xc6, 0xce, 0xde, 0xf6, 0xe6, 0x7c, 0x00, },	// 0x30  0
	{ 0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x00, },	// 0x31  1
	{ 0x78, 0xcc, 0x0c, 0x38, 0x60, 0xcc, 0xfc, 0x00, },	// 0x32  2
	{ 0x78, 0xcc, 0x0c, 0x38, 0x0c, 0xcc, 0x78, 0x00, },	// 0x33  3
	{ 0x1c, 0x3c, 0x6c, 0xcc, 0xfe, 0x0c, 0x1e, 0x00, },	// 0x34  4
	{ 0xfc, 0xc0, 0xf8, 0x0c, 0x0c, 0xcc, 0x78, 0x00, },	// 0x35  5
	{ 0x38, 0x60, 0xc0, 0xf8, 0xcc, 0xcc, 0x78, 0x00, },	// 0x36  6
	{ 0xfc, 0xcc, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x00, },	// 0x37  7
	{ 0x78, 0xcc, 0xcc, 0x78, 0xcc, 0xcc, 0x78, 0x00, },	// 0x38  8
	{ 0x78, 0xcc, 0xcc, 0x7c, 0x0c, 0x18, 0x70, 0x00, },	// 0x39  9
	{ 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00, },	// 0x3a  :
	{ 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x60, },	// 0x3b  ;
	{ 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x00, },	// 0x3c  <
	{ 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00, },	// 0x3d  =
	{ 0x60, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x60, 0x00, },	// 0x3e  >
	{ 0x78, 0xcc, 0x0c, 0x18, 0x30, 0x00, 0x30, 0x00, },	// 0x3f  ?
	{ 0x7c, 0xc6, 0xde, 0xde, 0xde, 0xc0, 0x78, 0x00, },	// 0x40  @
	{ 0x30, 0x78, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0x00, },	// 0x41  A
	{ 0xfc, 0x66, 0x66, 0x7c, 0x66, 0x66, 0xfc, 0x00, },	// 0x42  B
	{ 0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x00, },	// 0x43  C
	{ 0xf8, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0xf8, 0x00, },	// 0x44  D
	{ 0xfe, 0x62, 0x68, 0x78, 0x68, 0x62, 0xfe, 0x00, },	// 0x45  E
	{ 0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0xf0, 0x00, },	// 0x46  F
	{ 0x3c, 0x66, 0xc0, 0xc0, 0xce, 0x66, 0x3e, 0x00, },	// 0x47  G
	{ 0xcc, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0xcc, 0x00, },	// 0x48  H
	{ 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00, },	// 0x49  I
	{ 0x1e, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78, 0x00, },	// 0x4a  J
	{ 0xe6, 0x66, 0x6c, 0x78, 0x6c, 0x66, 0xe6, 0x00, },	// 0x4b  K
	{ 0xf0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xfe, 0x00, },	// 0x4c  L
	{ 0xc6, 0xee, 0xfe, 0xfe, 0xd6, 0xc6, 0xc6, 0x00, },	// 0x4d  M
	{ 0xc6, 0xe6, 0xf6, 0xde, 0xce, 0xc6, 0xc6, 0x00, },	// 0x4e  N
	{ 0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00, },	// 0x4f  O
	{ 0xfc, 0x66, 0x66, 0x7c, 0x60, 0x60, 0xf0, 0x00, },	// 0x50  P
	{ 0x78, 0xcc, 0xcc, 0xcc, 0xdc, 0x78, 0x1c, 0x00, },	// 0x51  Q
	{ 0xfc, 0x66, 0x66, 0x7c, 0x6c, 0x66, 0xe6, 0x00, },	// 0x52  R
	{ 0x78, 0xcc, 0xe0, 0x70, 0x1c, 0xcc, 0x78, 0x00, },	// 0x53  S
	{ 0xfc, 0xb4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00, },	// 0x54  T
	{ 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xfc, 0x00, },	// 0x55  U
	{ 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00, },	// 0x56  V
	{ 0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xee, 0xc6, 0x00, },	// 0x57  W
	{ 0xc6, 0xc6, 0x6c, 0x38, 0x38, 0x6c, 0xc6, 0x00, },	// 0x58  X
	{ 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x30, 0x78, 0x00, },	// 0x59  Y
	{ 0xfe, 0xc6, 0x8c, 0x18, 0x32, 0x66, 0xfe, 0x00, },	// 0x5a  Z
	{ 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00, },	// 0x5b  [
	{ 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02, 0x00, },	// 0x5c  '\'
	{ 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00, },	// 0x5d  ]
	{ 0x10, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00, },	// 0x5e  ^
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, },	// 0x5f  _
	{ 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, },	// 0x60  `
	{ 0x00, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x76, 0x00, },	// 0x61  a
	{ 0xe0, 0x60, 0x60, 0x7c, 0x66, 0x66, 0xdc, 0x00, },	// 0x62  b
	{ 0x00, 0x00, 0x78, 0xcc, 0xc0, 0xcc, 0x78, 0x00, },	// 0x63  c
	{ 0x1c, 0x0c, 0x0c, 0x7c, 0xcc, 0xcc, 0x76, 0x00, },	// 0x64  d
	{ 0x00, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00, },	// 0x65  e
	{ 0x38, 0x6c, 0x60, 0xf0, 0x60, 0x60, 0xf0, 0x00, },	// 0x66  f
	{ 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8, },	// 0x67  g
	{ 0xe0, 0x60, 0x6c, 0x76, 0x66, 0x66, 0xe6, 0x00, },	// 0x68  h
	{ 0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00, },	// 0x69  i
	{ 0x0c, 0x00, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78, },	// 0x6a  j
	{ 0xe0, 0x60, 0x66, 0x6c, 0x78, 0x6c, 0xe6, 0x00, },	// 0x6b  k
	{ 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00, },	// 0x6c  l
	{ 0x00, 0x00, 0xcc, 0xfe, 0xfe, 0xd6, 0xc6, 0x00, },	// 0x6d  m
	{ 0x00, 0x00, 0xf8, 0xcc, 0xcc, 0xcc, 0xcc, 0x00, },	// 0x6e  n
	{ 0x00, 0x00, 0x78, 0xcc, 0xcc, 0xcc, 0x78, 0x00, },	// 0x6f  o
	{ 0x00, 0x00, 0xdc, 0x66, 0x66, 0x7c, 0x60, 0xf0, },	// 0x70  p
	{ 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0x1e, },	// 0x71  q
	{ 0x00, 0x00, 0xdc, 0x76, 0x66, 0x60, 0xf0, 0x00, },	// 0x72  r
	{ 0x00, 0x00, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x00, },	// 0x73  s
	{ 0x10, 0x30, 0x7c, 0x30, 0x30, 0x34, 0x18, 0x00, },	// 0x74  t
	{ 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0x76, 0x00, },	// 0x75  u
	{ 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00, },	// 0x76  v
	{ 0x00, 0x00, 0xc6, 0xd6, 0xfe, 0xfe, 0x6c, 0x00, },	// 0x77  w
	{ 0x00, 0x00, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0x00, },	// 0x78  x
	{ 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8, },	// 0x79  y
	{ 0x00, 0x00, 0xfc, 0x98, 0x30, 0x64, 0xfc, 0x00, },	// 0x7a  z
	{ 0x1c, 0x30, 0x30, 0xe0, 0x30, 0x30, 0x1c, 0x00, },	// 0x7b  {
	{ 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00, },	// 0x7c  |
	{ 0xe0, 0x30, 0x30, 0x1c, 0x30, 0x30, 0xe0, 0x00, },	// 0x7d  }
	{ 0x76, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, },	// 0x7e  ~
	{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, },	// block cursor
};
#endif /* __FONT_H__ */
