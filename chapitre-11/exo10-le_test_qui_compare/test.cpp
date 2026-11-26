#include <iostream>

struct Vec2i {
    long long x = 0;
    long long z = 0;
};

static Vec2i right_vector(long long yaw) {
    switch (((yaw % 4) + 4) % 4) {
        case 0:
            return {1LL, 0LL};
        case 1:
            return {0LL, -1LL};
        case 2:
            return {-1LL, 0LL};
        case 3:
        default:
            return {0LL, 1LL};
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long hz = 0;
    long long ipd = 0;
    long long N = 0;
    if (!(std::cin >> hz >> ipd >> N)) {
        return 0;
    }

    long long x0 = 0;
    long long y0 = 0;
    long long z0 = 0;
    long long k0 = 0;
    long long dk = 0;
    long long vx = 0;
    if (!(std::cin >> x0 >> y0 >> z0 >> k0 >> dk >> vx)) {
        return 0;
    }

    const long long effective_hz = (hz <= 1LL) ? 72LL : hz;
    const long long period = 1000000000LL / effective_hz;
    const long long half_ipd = ipd / 2LL;

    std::cout << "PERIODE " << period << '\n';

    for (long long t = 1; t <= N; ++t) {
        const long long step = t - 1;
        const long long yaw = (((k0 + step * dk) % 4LL) + 4LL) % 4LL;
        const long long hx = x0 + step * vx;
        const long long hy = y0;
        const long long hz_pos = z0;

        const Vec2i right = right_vector(yaw);

        const long long gx = hx - half_ipd * right.x;
        const long long gy = hy;
        const long long gz = hz_pos - half_ipd * right.z;

        const long long dx = hx + half_ipd * right.x;
        const long long dy = hy;
        const long long dz = hz_pos + half_ipd * right.z;

        const long long instant = t * period;

        std::cout << t << " G " << gx << ' ' << gy << ' ' << gz
                  << " D " << dx << ' ' << dy << ' ' << dz
                  << " I " << instant << '\n';
    }

    return 0;
}