#version 450

#define MAX_NB_LIGHTS 16
#define M_PI 3.141592

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 albedo;
layout(location = 3) in float roughness;
layout(location = 4) in float metallic;

layout(location = 0) out vec4 outFragColor;

layout(std140, binding = 0) uniform uCamera {
    mat4 view;
    mat4 proj;
    vec3 pos;
}
camera;

layout(std140, binding = 1) uniform uLight {
    vec4 pos[MAX_NB_LIGHTS];
    vec4 color[MAX_NB_LIGHTS];
    vec4 intensity[MAX_NB_LIGHTS];
    float count;
}
light;

vec4 sRGBToLinear(in vec4 value) {
    return vec4(mix(pow(value.rgb * 0.9478672986 + vec3(0.0521327014), vec3(2.4)),
                    value.rgb * 0.0773993808, vec3(lessThanEqual(value.rgb, vec3(0.04045)))),
                value.a);
}

vec4 LinearTosRGB(in vec4 value) {
    return vec4(mix(pow(value.rgb, vec3(0.41666)) * 1.055 - vec3(0.055), value.rgb * 12.92,
                    vec3(lessThanEqual(value.rgb, vec3(0.0031308)))),
                value.a);
}

vec3 lambertianDiffuse(vec3 albedo) {
    return albedo / M_PI;
}

float TrowbridgeReitz(vec3 n, vec3 h, float alpha) {
    alpha = alpha * alpha / 2.0;
    float alpha2 = pow(alpha, 2.0);
    return alpha2 / (M_PI * pow(pow(max(dot(n, h), 0.0), 2.0) * (alpha2 - 1.0) + 1.0, 2.0));
}

float SmithMasking(vec3 n, vec3 v, float k) {
    // taken from
    // https://google.github.io/filament/Filament.html#materialsystem/specularbrdf
    // seems to give better results
    k = k * k / 2.0;
    float ndotv = max(dot(n, v), 0.01);
    return (2.0 * ndotv) / (ndotv + sqrt(pow(k, 2.0) + (1.0 - pow(k, 2.0)) * pow(ndotv, 2.0)));
    // return max(dot(n, v), 0.01) / (max(dot(n, v), 0.01) * (1.0 - k) + k);
}

vec3 FresnelSchlick(vec3 n, vec3 v, vec3 f0) {
    return f0 + (1.0 - f0) * pow(1.0 - dot(n, v), 5.0);
}

vec3 CookTorranceSpecular(vec3 wo, vec3 wi, vec3 n, float roughness) {
    vec3 h = normalize(wi + wo);
    vec3 D = vec3(TrowbridgeReitz(n, h, max(roughness, 0.05)));
    vec3 G =
        vec3(SmithMasking(n, wo, max(roughness, 0.05)) * SmithMasking(n, wi, max(roughness, 0.05)));
    return D * G / max((4.0 * max(dot(wo, n), 0.0) * max(dot(wi, n), 0.0)), 0.01);
}

void main() {
    vec3 wo = camera.pos - pos;
    vec3 f0 = mix(vec3(0.04), sRGBToLinear(vec4(albedo, 1.0)).rgb, metallic);
    vec3 irradiance = vec3(0.0);
    for (int i = 0; i < light.count; ++i) {
        vec3 wi = normalize(light.pos[i].xyz - pos);
        vec3 h = normalize(wi + wo);
        vec3 kS = FresnelSchlick(wi, wo, f0);
        vec3 diffuseBRDFEval = (1.0 - metallic) * lambertianDiffuse(sRGBToLinear(vec4(albedo, 1.0)).rgb);
        vec3 specularBRDFEval = CookTorranceSpecular(wo, wi, normal, roughness);
        irradiance += (kS * specularBRDFEval) * light.color[i].rgb *
                      max(dot(normal, wi), 0.01);
    }
    irradiance /= (irradiance + 1.0);
    outFragColor.rgba = LinearTosRGB(vec4(irradiance, 1.0));
}