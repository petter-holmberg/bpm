import std;
import bpm;

inline constexpr std::array color_bars
{
    bpm::white,
    bpm::yellow,
    bpm::cyan,
    bpm::lime,
    bpm::magenta,
    bpm::red,
    bpm::blue,
    bpm::black,
};

void draw_color_bars(bpm::frame& frame, bpm::vector2d window_size)
{
    int x = 0;
    int const w = window_size.x / std::int32_t(color_bars.size());
    int const h = window_size.y;

    std::ranges::for_each(color_bars, [&](auto color) mutable
    {
        frame(bpm::rectangle{{w, h}, color}, {x, 0});
        x += w;
    });
}

void draw_corner_pixels(bpm::frame& frame, bpm::vector2d window_size)
{
    frame(bpm::pixel{bpm::black}, {0, 0});
    frame(bpm::pixel{bpm::black}, {0, window_size.y - 1});
    frame(bpm::pixel{bpm::white}, {window_size.x - 1, 0});
    frame(bpm::pixel{bpm::white}, {window_size.x - 1, window_size.y - 1});
}

void draw_transition(bpm::frame& frame, bpm::vector2d window_size)
{
    bpm::point2d pos = {10, window_size.y - window_size.y / 20 - window_size.y / 40};
    bpm::vector2d size = {window_size.x - 20, window_size.y / 20};
    frame(bpm::rectangle{size, bpm::black}, pos);

    for (auto x = 0; x < size.x - 4; ++x) {
        float fraction = float(size.x - 4 - x) / (size.x - 4);
        frame(
            bpm::line2d{{0, size.y - 4},
            bpm::blend(bpm::black, bpm::white, fraction)},
            {x + pos.x + 2, pos.y + 2}
        );
    }
}

void draw_circle(bpm::frame& frame, bpm::vector2d window_size)
{
    frame(bpm::circle{window_size.y * .4f, {0, 0, 0, 127}}, bpm::point2d{0, 0} + window_size / 2);
}

void draw_triangles(bpm::frame& frame, bpm::vector2d window_size)
{
    frame(
        bpm::triangle{{-200, -200}, {200, -200}, bpm::gray},
        bpm::point2d{0, 0} + window_size / 2 + bpm::vector2d{0, 200}
    );
    frame(
        bpm::triangle{{200, 200}, {-200, 200}, bpm::blend(bpm::black, bpm::white, .5f)},
        bpm::point2d{0, 0} + window_size / 2 - bpm::vector2d{0, 200}
    );
}

void draw_texture(bpm::frame& frame, bpm::texture const& tex, bpm::vector2d window_size)
{
    frame(tex, bpm::point2d{0, 0} + window_size / 16);
    frame(tex, {.size{tex.size() / 2}}, bpm::point2d{0, 0} + window_size / 16);
    frame(
        tex,
        {.size{tex.size() / 2}},
        {
            .pivot{tex.size() / 2},
            .rotation{.degrees{45.f}},
            .scale{.5f},
        },
        bpm::point2d{0, 0} + window_size / 16
    );
}

void draw_text(bpm::frame& frame, bpm::text const& txt, bpm::vector2d window_size)
{
    frame(txt, bpm::point2d{0, 0} + window_size / 2 - txt.size() / 2);
}

int main()
{
    bpm::window w;
    auto const window_size = w.size();

    bpm::image img{{16, 16}};
    img({0, 0}) = bpm::black;
    img({1, 1}) = bpm::black;
    img({15, 0}) = bpm::black;
    img({14, 1}) = bpm::black;
    img({1, 14}) = bpm::black;
    img({0, 15}) = bpm::black;
    img({14, 14}) = bpm::black;
    img({15, 15}) = bpm::black;

    bpm::texture im_tex{w, img};

    bpm::texture tex{w, w.size() / 16, {255, 0, 0, 127}};
    tex.resize(tex.size() * 2);

    bpm::font notosa{w, 48, bpm::font_noto_sans_regular};
    bpm::font notosm{w, 48, bpm::font_noto_sans_mono_regular};
    bpm::font notoss{w, 48, bpm::font_noto_serif_regular};
    bpm::text sentence0{"The quick brown fox jumps over the lazy dog!", notosa, bpm::white};
    bpm::text sentence1{"The quick brown fox jumps over the lazy dog!", notosm, bpm::white};
    bpm::text sentence2{"The quick brown fox jumps over the lazy dog!", notoss, bpm::white};

    for (auto frame : w)
    {
        frame(bpm::black);
        draw_color_bars(frame, window_size);
        draw_corner_pixels(frame, window_size);
        draw_transition(frame, window_size);
        draw_circle(frame, window_size);
        if (bpm::key_down(bpm::key::enter) || bpm::mouse_button(0)) {
            draw_triangles(frame, window_size);
        }
        draw_texture(frame, tex, window_size);
        frame(im_tex, bpm::point2d{16, 16});
        draw_text(frame, sentence0, window_size - bpm::vector2d{0, 96});
        draw_text(frame, sentence1, window_size);
        draw_text(frame, sentence2, window_size + bpm::vector2d{0, 96});
    }
}
