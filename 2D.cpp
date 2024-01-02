#include "2D.h"
//projection
Vec4 proj(Vec4 point) {
	return(scale(point, { 1 / point[2], 1 / point[2] , 1 , 1 }));
}

