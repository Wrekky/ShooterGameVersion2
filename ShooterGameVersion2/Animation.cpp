#include "Animation.h"
void Animation::Animate() {
	if (currentImageCount < count) {
		currentImageCount++;
	}
	else {
		currentImageCount = 0;
	}
}
void Animation::Reset() {
	currentImageCount = 0;
}