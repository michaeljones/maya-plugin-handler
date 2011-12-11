
#include "OpinionatedPluginHandler.hh"

#include "examples.hh"

#include <maya/MFnPlugin.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>

template< class OpinionatedPluginHandlerT >
MStatus handlePlugin( OpinionatedPluginHandlerT& handler )
{
    MStatus status;

    handler.template handleNode< Locator >();
    handler.template handleCommand< Command >();

    return status;
}


MStatus initializePlugin( MObject obj )
{
    MStatus result;
    MFnPlugin plugin( obj, "Michael Jones", "0.1", "Any");

    InitializeOpinionatedPluginHandler handler( plugin );
    handlePlugin( handler );

    return result;
}

MStatus uninitializePlugin( MObject obj)
{
    MStatus result;

    MFnPlugin plugin( obj );

    UninitializeOpinionatedPluginHandler handler( plugin );
    handlePlugin( handler );

    return result;
}


