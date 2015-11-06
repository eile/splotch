
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

    loader->load( 0.f );
    const fivox::Events& events = loader->getEvents();
    points.reserve( events.size( ));
    COLOUR colours[] =
        {{ 1.000000, 0.000000, 0.600000 },
         { 1.000000, 0.600000, 0.000000 },
         { 0.000000, 0.600000, 1.000000 },
         { 0.000000, 1.000000, 0.000000 },
         { 0.600000, 0.000000, 0.000000 },
         { 1.000000, 0.000000, 0.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 0.000000, 0.000000, 1.000000 },
         { 0.000000, 0.600000, 0.000000 },
         { 1.000000, 1.000000, 0.000000 },
         { 1.000000, 0.000000, 1.000000 },
         { 0.600000, 0.600000, 0.000000 },
         { 0.600000, 0.000000, 1.000000 },
         { 0.600000, 1.000000, 0.000000 },
         { 0.600000, 0.000000, 0.600000 },
         { 0.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 0.000000, 0.000000, 1.000000 },
         { 0.000000, 0.600000, 0.000000 },
         { 1.000000, 1.000000, 0.000000 },
         { 1.000000, 0.000000, 1.000000 },
         { 0.600000, 0.600000, 0.000000 },
         { 0.600000, 0.000000, 1.000000 },
         { 0.600000, 1.000000, 0.000000 },
         { 0.600000, 0.000000, 0.600000 },
         { 0.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 0.000000, 0.000000, 1.000000 },
         { 0.000000, 0.600000, 0.000000 },
         { 1.000000, 1.000000, 0.000000 },
         { 1.000000, 0.000000, 1.000000 },
         { 0.600000, 0.600000, 0.000000 },
         { 0.600000, 0.000000, 1.000000 },
         { 0.600000, 1.000000, 0.000000 },
         { 0.600000, 0.000000, 0.600000 },
         { 0.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 1.000000, 1.000000, 1.000000 },
         { 0.000000, 0.000000, 1.000000 },
         { 0.000000, 0.600000, 0.000000 },
         { 1.000000, 1.000000, 0.000000 },
         { 1.000000, 0.000000, 1.000000 },
         { 0.600000, 0.600000, 0.000000 },
         { 0.600000, 0.000000, 1.000000 },
         { 0.600000, 1.000000, 0.000000 },
         { 0.600000, 0.000000, 0.600000 },
         { 0.000000, 1.000000, 1.000000 }};

    for( const fivox::Event& event : events )
        points.emplace_back(
            particle_sim( colours[ std::min( int( event.value ), 54 ) ],
                          event.position.x(), event.position.z(),
                          event.position.y(), event.value > 0. ? 32.f : 8.f,
                          1.f, 0 /* type */, true  /* active */ ));
}
