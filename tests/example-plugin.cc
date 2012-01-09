
#include "PluginHandler.hh"

#include "examples.hh"

#include <maya/MFnPlugin.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>

MStatus handlePlugin( mph::PluginHandler& handler )
{
    MStatus status;
    status = handler.handleNode(
            "locatorExample",
            Locator::id,
            Locator::creator,
            Locator::initialize,
            MPxNode::kLocatorNode
            );

    status = handler.handleCommand(
            "commandExample",
            Command::creator,
            Command::syntaxCreator
            );

    status = handler.handleData(
            "dataExample",
            Data::id,
            Data::creator
            );

    return status;
}


MStatus initializePlugin( MObject obj )
{
    MStatus result;
    MFnPlugin plugin( obj, "Michael Jones", "0.1", "Any");

    mph::InitializePluginHandler handler( plugin );
    handlePlugin( handler );

    return result;
}

MStatus uninitializePlugin( MObject obj)
{
    MStatus result;

    MFnPlugin plugin( obj );

    mph::UninitializePluginHandler handler( plugin );
    handlePlugin( handler );

    return result;
}


