
/* Copyright (c) 2015, EPFL/Blue Brain Project
 *                     Stefan.Eilemann@epfl.ch
 */

#include "reader.h"
#include <fivox/fivox.h>

namespace
{
typedef itk::Image< uint8_t, 3 > Volume;
typedef Volume::Pointer VolumePtr;
typedef std::shared_ptr< fivox::EventFunctor< Volume >> FunctorPtr;
typedef fivox::FieldFunctor< Volume > FieldFunctor;
typedef std::shared_ptr< FieldFunctor > FieldFunctorPtr;
typedef fivox::ImageSource< Volume > ImageSource;
typedef ImageSource::Pointer ImageSourcePtr;
}

void fivox_reader(paramfile &file, std::vector<particle_sim> &points)
{
    fivox::URIHandler params( file.find< std::string >( "infile" ));
    ImageSourcePtr source = params.newImageSource< uint8_t >();
    FunctorPtr functor = source->getFunctor();
    fivox::EventSourcePtr loader = functor->getSource();

    loader->load( 5.f );
    const fivox::Events& events = loader->getEvents();
    points.reserve( events.size( ));
    const COLOUR colour( 1., 1., 1. );

    for( const fivox::Event& event : events )
        points.emplace_back(
            particle_sim( colour, event.position.x(), event.position.y(),
                          event.position.z(), 8.f, event.value, 0 /* type */,
                          event.value > 0.f ? true : false  /* active */ ));
}
