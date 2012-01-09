
#include "OpinionatedPluginHandler.hh"

#include "examples.hh"

#include <maya/MFnPlugin.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>

template< class OpinionatedPluginHandlerT >
MStatus handlePlugin( OpinionatedPluginHandlerT& handler )
{
    MStatus status;

    handler.template handleNode< FullOpinionatedLocator >();
    handler.template handleNode< PartialOpinionatedNode >();

    handler.template handleCommand< FullOpinionatedCommand >();
    handler.template handleCommand< PartialOpinionatedCommand >();

    handler.template handleData< FullOpinionatedData >();
    handler.template handleData< PartialOpinionatedData >();

    return status;
}


MStatus initializePlugin( MObject obj )
{
    MStatus result;
    MFnPlugin plugin( obj, "Michael Jones", "0.1", "Any");

    mph::InitializeOpinionatedPluginHandler handler( plugin );
    handlePlugin( handler );

    return result;
}

MStatus uninitializePlugin( MObject obj)
{
    MStatus result;

    MFnPlugin plugin( obj );

    mph::UninitializeOpinionatedPluginHandler handler( plugin );
    handlePlugin( handler );

    return result;
}


