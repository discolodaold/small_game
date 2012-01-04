#include "animation.h"
#include "sys.h"

#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

animation_easing(linear) {
    return t/d;
}

animation_easing(swing) {
    return (-cos(t/d*PI)/2.0f) + 0.5f;
}

animation_easing(easeInQuad) {
    return (t/=d)*t;
}

animation_easing(easeOutQuad) {
    return -(t/=d)*(t-2);
}

animation_easing(easeInOutQuad) {
    return ((t/=d/2) < 1) ? 0.5f*t*t : -0.5f * ((--t)*(t-2) - 1);
}

animation_easing(easeInCubic) {
    return (t/=d)*t*t;
}

animation_easing(easeOutCubic) {
    return ((t=t/d-1)*t*t + 1);
}

animation_easing(easeInOutCubic) {
    return ((t/=d/2) < 1) ? 0.5f*t*t*t : 0.5f*((t-=2)*t*t + 2);
}

animation_easing(easeInQuart) {
    return (t/=d)*t*t*t;
}

animation_easing(easeOutQuart) {
    return -((t=t/d-1)*t*t*t - 1);
}

animation_easing(easeInOutQuart) {
    return ((t/=d/2) < 1) ? 0.5f*t*t*t*t : -0.5f*((t-=2)*t*t*t - 2);
}

animation_easing(easeInQuint) {
    return (t/=d)*t*t*t*t;
}

animation_easing(easeOutQuint) {
    return ((t=t/d-1)*t*t*t*t + 1);
}

animation_easing(easeInOutQuint) {
    return ((t/=d/2) < 1) ? 0.5f*t*t*t*t*t : 0.5f*((t-=2)*t*t*t*t + 2);
}

animation_easing(easeInSine) {
    return -cos(t/d * (PI/2)) + 1.0f;
}

animation_easing(easeOutSine) {
    return sin(t/d * (PI/2));
}

animation_easing(easeInOutSine) {
    return -0.5f*(cos(PI*t/d) - 1);
}

animation_easing(easeInExpo) {
    return (t <= 0.0f) ? 0.0f : pow(2, 10 * (t/d - 1));
}

animation_easing(easeOutExpo) {
    return (t >= d) ? 1.0f : (-pow(2, -10 * t/d) + 1);
}

animation_easing(easeInOutExpo) {
    if(t<=0.0f) return 0.0f;
    if(t>=d) return 1.0f;
    return ((t/=d/2) < 1) ? 0.5f*pow(2, 10 * (t - 1)) : 0.5f*(-pow(2, -10 * --t) + 2);
}

animation_easing(easeInCirc) {
    return -(sqrt(1 - (t/=d)*t) - 1);
}

animation_easing(easeOutCirc) {
    return sqrt(1 - (t=t/d-1)*t);
}

animation_easing(easeInOutCirc) {
    return ((t/=d/2) < 1) ? -0.5f * (sqrt(1 - t*t) - 1) : 0.5f * (sqrt(1 - (t-=2)*t) + 1);
}

animation_easing(easeInElastic) {
    float s = 1.70158f;
    float p = 0.0f;
    if(t <= 0.0f) {
        return 0.0f;
    }
    if((t/=d) >= 1.0f) {
        return 1.0f;
    }
    if(!p) {
        p = d*0.3f;
    }
    s = p/(2*PI) * 1.57f; // asin(1.0f);
    return -(pow(2,10*(t-=1)) * sin((t*d-s)*(2*PI)/p ));
}

animation_easing(easeOutElastic) {
    float s = 1.70158f;
    float p = 0.0f;
    if(t <= 0.0f) {
        return 0.0f;
    }
    if((t/=d) >= 1.0f) {
        return 1.0f;
    }
    if(!p) {
        p = d*0.3f;
    }
    s = p/(2*PI) * 1.57f; // asin(1.0f);
    return pow(2,-10*t) * sin((t*d-s)*(2*PI)/p) + 1.0f;
}

animation_easing(easeInOutElastic) {
    float s = 1.70158f;
    float p = 0;
    if(t <= 0.0f) {
        return 0.0f;
    }
    if((t/=d/2)==2) {
        return 1.0f;
    }
    if(!p) {
        p=d*(0.3f*1.5f);
    }
    s = p/(2*PI) * 1.57f;// asin(1.0f)
    return (t < 1) ? -0.5f*(pow(2,10*(t-=1)) * sin( (t*d-s)*(2*PI)/p )) : pow(2,-10*(t-=1)) * sin( (t*d-s)*(2*PI)/p )*0.5f + 1.0f;
}

animation_easing(easeInBack) {
    float s = 1.70158;
    return (t/=d)*t*((s+1)*t - s);
}

animation_easing(easeOutBack) {
    float s = 1.70158;
    return ((t=t/d-1)*t*((s+1)*t + s) + 1);
}

animation_easing(easeInOutBack) {
    float s = 1.70158;
    return ((t/=d/2) < 1) ?  0.5f*(t*t*(((s*=(1.525))+1)*t - s)) : 0.5f*((t-=2)*t*(((s*=(1.525))+1)*t + s) + 2);
}

animation_easing(easeInBounce) {
    return 1.0f - easeOutBounce(d-t, d);
}

animation_easing(easeOutBounce) {
    if((t/=d) < (1/2.75)) {
        return (7.5625*t*t);
    } else if(t < (2/2.75)) {
        return (7.5625*(t-=(1.5/2.75))*t + .75);
    } else if(t < (2.5/2.75)) {
        return (7.5625*(t-=(2.25/2.75))*t + .9375);
    } else {
        return (7.5625*(t-=(2.625/2.75))*t + .984375);
    }
}

animation_easing(easeInOutBounce) {
    return (t < d/2) ? easeInBounce(t*2, d) * 0.5f : easeOutBounce(t*2-d, d) * 0.5f + 0.5f;
}

struct animation {
    struct proc *proc;
    void (*func)(struct animation *, float value);
    float duration;
    float startTime;
    float (*easing)(float t, float d);
    union {
        struct {
            int start;
            int difference;
            int *ptr;
        } integer;
    };
};

static void _doInt(struct animation *animation, float time) {
    *animation->integer.ptr = animation->integer.start + (int)(animation->integer.difference*time);
}

static proc(animation_func) {
    struct animation *animation;
    float elapsed_time;

    animation = (struct animation *)data;
    elapsed_time = current_time - animation->startTime;

    proc_begin();
    while(elapsed_time < animation->duration) {
        if(proc_receive("animation stop")) {
            proc_exit();
        }
        animation->func(animation, animation->easing(elapsed_time, animation->duration));
        proc_yield();
    }
    proc_send(animation->proc, "animation end", proc_current());
    free(data);
    proc_end();
}

struct proc *animate_int(struct proc *proc, int *intPtr, int from, int to, float duration, float (*easing)(float t, float d)) {
    struct animation *animation = malloc(sizeof(*animation));
    animation->proc = proc;
    animation->func = _doInt;
    animation->duration = duration;
    animation->startTime = current_time;
    animation->easing = easing;
    animation->integer.start = from;
    animation->integer.difference = to - from;
    animation->integer.ptr = intPtr;
    return proc_spawn(animation_func, animation);
}

