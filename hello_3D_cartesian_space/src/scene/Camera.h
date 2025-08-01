#pragma once
#include "../math/Math.h"

// Simple orbit/pan/zoom camera around a target (center).
// - yaw, pitch in radians; radius is distance from center.
class Camera {
public:
    Vec3 center{0,0,0};
    float yaw = 0.785398163f;   // 45 degrees
    float pitch = 0.6f;         // ~34 degrees
    float radius = 16.0f;       // distance to target
    float minRadius = 1.0f;
    float maxPitch = 1.55f;     // just below 90 deg to avoid gimbal lock
    float minPitch = -1.55f;

    Vec3 upWorld{0,1,0};

    Vec3 eye() const {
        float cp = std::cos(pitch), sp = std::sin(pitch);
        float cy = std::cos(yaw),   sy = std::sin(yaw);
        return Vec3{
            center.x + radius * cp * cy,
            center.y + radius * sp,
            center.z + radius * cp * sy
        };
    }

    Mat4 view() const {
        return lookAt(eye(), center, upWorld);
    }

    void orbit(float dYaw, float dPitch) {
        yaw += dYaw;
        pitch += dPitch;
        if (pitch > maxPitch) pitch = maxPitch;
        if (pitch < minPitch) pitch = minPitch;
    }

    void zoom(float factor) {
        radius *= factor;
        if (radius < minRadius) radius = minRadius;
    }

    void pan(float dx, float dy) {
        // Pan along camera right and up directions
        // Compute camera basis from yaw/pitch
        float cp = std::cos(pitch), sp = std::sin(pitch);
        float cy = std::cos(yaw),   sy = std::sin(yaw);

        // Forward
        Vec3 f{ cp*cy, sp, cp*sy };
        // Right = normalize(cross(forward, upWorld))
        Vec3 r{ f.y*upWorld.z - f.z*upWorld.y, f.z*upWorld.x - f.x*upWorld.z, f.x*upWorld.y - f.y*upWorld.x };
        float rl = std::sqrt(r.x*r.x + r.y*r.y + r.z*r.z);
        if (rl > 1e-6f) { r.x/=rl; r.y/=rl; r.z/=rl; }
        // Up = cross(right, forward)
        Vec3 u{ r.y*f.z - r.z*f.y, r.z*f.x - r.x*f.z, r.x*f.y - r.y*f.x };

        center.x += (-dx) * r.x + (dy) * u.x;
        center.y += (-dx) * r.y + (dy) * u.y;
        center.z += (-dx) * r.z + (dy) * u.z;
    }
};
