/*
    This file is part of darts – the Dartmouth Academic Ray Tracing Skeleton.

    Copyright (c) 2017-2025 by Wojciech Jarosz
*/
#pragma once

#include <darts/factory.h>
#include <darts/math.h>
#include <memory>

/**
    Abstract sample generator.

    A sample generator is responsible for generating the random number stream that will be passed to an #Integrator
    implementation as it computes the radiance incident along a specified ray.

    \ingroup Samplers
*/
class Sampler
{
protected:
    uint32_t m_base_seed         = 0u;
    uint32_t m_samples_per_pixel = 1u;
    uint32_t m_sample_index      = 0u;
    uint32_t m_dimension         = 0u;
    Vec2i    m_pixel             = {0, 0};

public:
    Sampler() = default;

    virtual ~Sampler() {}

    /// Create an exact copy of this Sampler instance
    virtual std::unique_ptr<Sampler> clone() const = 0;

    /**
        Set the base seed for the sampler (passed in as a command-line argument).

        Setting the seed of the underlying RNG deterministically is important to produce identical results between runs.

        This function should only need to be called once before rendering starts.
    */
    virtual void set_base_seed(uint32_t s) { m_base_seed = s; }

    /**
        Prepare to generate samples for pixel (x,y).

        This function is called every time the integrator starts rendering a new pixel.

        The base class simply stores the pixel coordinates and sample index, and resets the dimension to zero.
    */
    virtual void start_pixel(const Vec2i &pixel, uint32_t index)
    {
        m_pixel        = pixel;
        m_sample_index = index;
        m_dimension    = 0u;
    }

    /// Retrieve the next float value (dimension) from the current sample
    virtual float next1f() = 0;

    /// Retrieve the next two float values (dimensions) from the current sample
    virtual Vec2f next2f() = 0;

    /// Return the number of configured pixel samples
    uint32_t samples_per_pixel() const { return m_samples_per_pixel; }

    uint32_t  sample_index() const { return m_sample_index; }
    uint32_t &sample_index() { return m_sample_index; }
};

/**
    \file
    \brief Class #Sampler
*/
