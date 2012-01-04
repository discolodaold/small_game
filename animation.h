#ifndef ANIMATION_H
#define ANIMATION_H

#include "proc.h"

#define animation_easing(NAME) float NAME(float t, float d)
animation_easing(linear);
animation_easing(swing);
animation_easing(easeInQuad);
animation_easing(easeOutQuad);
animation_easing(easeInOutQuad);
animation_easing(easeInCubic);
animation_easing(easeOutCubic);
animation_easing(easeInOutCubic);
animation_easing(easeInQuart);
animation_easing(easeOutQuart);
animation_easing(easeInOutQuart);
animation_easing(easeInQuint);
animation_easing(easeOutQuint);
animation_easing(easeInOutQuint);
animation_easing(easeInSine);
animation_easing(easeOutSine);
animation_easing(easeInOutSine);
animation_easing(easeInExpo);
animation_easing(easeOutExpo);
animation_easing(easeInOutExpo);
animation_easing(easeInCirc);
animation_easing(easeOutCirc);
animation_easing(easeInOutCirc);
animation_easing(easeInElastic);
animation_easing(easeOutElastic);
animation_easing(easeInOutElastic);
animation_easing(easeInBack);
animation_easing(easeOutBack);
animation_easing(easeInOutBack);
animation_easing(easeInBounce);
animation_easing(easeOutBounce);
animation_easing(easeInOutBounce);

struct proc *animate_int(struct proc *proc, int *intPtr, int from, int to, float duration, float (*easing)(float t, float d));

#endif
