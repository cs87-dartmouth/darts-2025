/*
    This file is part of darts – the Dartmouth Academic Ray Tracing Skeleton.

    Copyright (c) 2017-2025 by Wojciech Jarosz
*/

#include <darts/sampler.h>
#include <darts/sampling.h>

/**
    Independent sampling - returns independent uniformly distributed random numbers in \f$[0, 1)\f$.

    This class is essentially just a wrapper around a pseudorandom number generator. For more details on what
    sample generators do in general, refer to the #Sampler class.

    \ingroup Samplers
*/
class IndependentSampler : public Sampler
{
public:
    IndependentSampler(const json &j) { m_samples_per_pixel = j.at("samples").get<int>(); }

    /**
        Create an exact clone of the current instance

        This is useful if you want to duplicate a sampler to use in multiple threads
    */
    std::unique_ptr<Sampler> clone() const override
    {
        std::unique_ptr<IndependentSampler> cloned(new IndependentSampler());
        cloned->m_samples_per_pixel = m_samples_per_pixel;
        cloned->m_base_seed         = m_base_seed;
        cloned->m_samples_per_pixel = m_samples_per_pixel;
        cloned->m_sample_index      = m_sample_index;
        cloned->m_dimension         = m_dimension;
        cloned->m_pixel             = m_pixel;

        cloned->m_rng = m_rng;
        return std::move(cloned);
    }

    void start_pixel(const Vec2i &pixel, uint32_t index) override
    {
        Sampler::start_pixel(pixel, index);
        m_rng.seed(hash(pixel, m_base_seed));
        m_rng.advance(m_sample_index);
    }

    float next1f() override
    {
        m_dimension++;
        return m_rng.rand1f();
    }

    Vec2f next2f() override
    {
        m_dimension += 2;
        return m_rng.rand2f();
    }

protected:
    IndependentSampler() {}

    RNG m_rng;
};

DARTS_REGISTER_CLASS_IN_FACTORY(Sampler, IndependentSampler, "independent")

/**
    \file
    \brief IndependentSampler Sampler
*/
