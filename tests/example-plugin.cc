
#include "PluginHandler.hh"

#include "examples.hh"

#include <maya/MFnPlugin.h>
#include <maya/MObject.h>
#include <maya/MStatus.h>

MStatus handlePlugin( PluginHandler& handler )
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

    return status;
}


MStatus initializePlugin( MObject obj )
{
    MStatus result;
    MFnPlugin plugin( obj, "Michael Jones", "0.1", "Any");

    InitializePluginHandler handler( plugin );
    handlePlugin( handler );

    return result;
}

MStatus uninitializePlugin( MObject obj)
{
    MStatus result;

    MFnPlugin plugin( obj );

    UninitializePluginHandler handler( plugin );
    handlePlugin( handler );

    return result;
}

