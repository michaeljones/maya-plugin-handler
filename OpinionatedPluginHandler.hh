#ifndef OPINIONATEDPLUGINHANDLER_HH
#define OPINIONATEDPLUGINHANDLER_HH

#include <maya/MFnPlugin.h>

class InitializeOpinionatedPluginHandler
{
public:

    InitializeOpinionatedPluginHandler( MFnPlugin& pluginFn )
     : m_pluginFn( pluginFn ) {}

    template< class NodeT >
    MStatus handleNode()
    {
        return m_pluginFn.registerNode(
                NodeT::nodeName,
                NodeT::id,
                NodeT::creator,
                NodeT::initialize,
                NodeT::nodeType,
                NodeT::classification
                );
    }

    template< class CommandT >
    MStatus handleCommand()
    {
        return m_pluginFn.registerCommand(
                CommandT::commandName,
                CommandT::creator,
                CommandT::syntaxCreator
                );
    }

private:

    MFnPlugin& m_pluginFn;
};


class UninitializeOpinionatedPluginHandler
{
public:

    UninitializeOpinionatedPluginHandler( MFnPlugin& pluginFn )
     : m_pluginFn( pluginFn ) {}

    template< class NodeT >
    MStatus handleNode()
    {
        return m_pluginFn.deregisterNode( NodeT::id );
    }

    template< class CommandT >
    MStatus handleCommand()
    {
        return m_pluginFn.deregisterCommand( CommandT::commandName );
    }

private:

    MFnPlugin& m_pluginFn;
};

#endif // OPINIONATEDPLUGINHANDLER_HH


