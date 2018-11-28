#include <math.h>

#include "../utils/image.h"
#include "../utils/math.h"
#include "preprocessing.h"

static int compute_raycast_sum(SDL_Surface *image, int h, double angle)
{
    angle = to_radians(angle);
    int ray = abs(cos(angle) * image->w);
    int w_start = (image->w - ray) / 2;

    int sum = 0;
    for (int w = w_start; w < w_start + ray; w++)
    {
        int nh = h + tan(angle) * w;
        if (nh >= 0 && nh < image->h && !is_white_pixel(image, nh, w))
            sum++;
    }
    return sum;
}

// https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
static double compute_variance(SDL_Surface *image, double angle)
{
    // Less accuracy, but faster result
    int h_start = image->h / 8;
    int h_len = (7 * image->h) / 8;
    double k = image->w / 15.;

    double sum = 0.;
    double sum_sq = 0.;
    for (int h = h_start; h < h_start + h_len; h += 4)
    {
        int s = compute_raycast_sum(image, h, angle);
        sum += s - k;
        sum_sq += (s - k) * (s - k);
    }
    return (sum_sq - (sum * sum) / h_len) / (h_len - 1);
}

static double find_skew_angle(
    SDL_Surface *image,
    double lower_bound, double upper_bound, double precision)
{
    double skew_angle = 0.;
    double max_variance = 0.;

    for (double angle = lower_bound; angle <= upper_bound; angle += precision)
    {
        double variance = compute_variance(image, angle);
        if (variance > max_variance)
        {
            max_variance = variance;
            skew_angle = angle;
        }
    }

    return skew_angle;
}

SDL_Surface *image_deskew(SDL_Surface *image)
{
    double skew_angle = find_skew_angle(image, -15., +15., 1.);
    skew_angle = find_skew_angle(image, skew_angle - 3, skew_angle + 3, 0.1);

    SDL_Surface *output = image_rotate(image, skew_angle);
    return output;
}
