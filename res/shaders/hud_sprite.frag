#version 330

in vec2 texCoord;
uniform vec4 inColor;
uniform sampler2D tex;
uniform bool hasTex;
uniform vec2 size;
uniform float radius;
uniform float frameSize;
uniform bool frameRounded;
uniform vec4 frameColor;

out vec4 color;

void main() {
    vec2 coord = texCoord;
    coord *= size;
    coord -= size / 2;
    vec2 quarterPos = abs(coord);
    if (radius > 0) {
        float radiusPx = min(size.x, size.y) * radius;
        vec2 centerPos = size / 2 - vec2(radiusPx);
        if (quarterPos.x < centerPos.x || quarterPos.y < centerPos.y) {
            // is not in corner, continue
        } else if (length(quarterPos - centerPos) > radiusPx)
            discard;
    }
    if (frameSize > 0) {
        vec2 dist = size/2 - quarterPos;
        if (dist.x < frameSize || dist.y < frameSize) {
            color = frameColor;
            return;
        }
        else if (frameRounded && radius > 0) {
            float radiusPx = min(size.x, size.y) * radius - frameSize;  // subtracting frame size here improves the frame width at the edges a little bit, making it visually more consistent
            vec2 centerPos = size / 2 - vec2(radiusPx) - vec2(frameSize);
            if (quarterPos.x < centerPos.x || quarterPos.y < centerPos.y) {
                // is not in corner, continue
            } else if (length(quarterPos - centerPos) > radiusPx) {
                color = frameColor;
                return;
            }
        }
    }

    if (hasTex) color = texture(tex, texCoord) * inColor;
    else color = inColor;
}