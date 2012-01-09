#ifndef PLUGINHANDLER_HH
#define PLUGINHANDLER_HH

#include <maya/MFnPlugin.h>

class PluginHandler 
{
public:

    virtual ~PluginHandler() {}

    virtual MStatus handleNode(
            const MString& typeName,
            const MTypeId& typeId,
            MCreatorFunction creatorFunction,
            MInitializeFunction initFunction,
            MPxNode::Type type = MPxNode::kDependNode,
            const MString* classification = NULL
            ) = 0;

    virtual MStatus handleCommand(
            const MString& commandName,
            MCreatorFunction creatorFunction,
            MCreateSyntaxFunction createSyntaxFunction = NULL
            ) = 0;

    virtual MStatus handleData(
            const MString& typeName,
            const MTypeId& typeId,
            MCreatorFunction creatorFunction,
            MPxData::Type type = MPxData::kData
            ) = 0;

    virtual MStatus handleControlCommand(
            const MString& commandName,
            MCreatorFunction creatorFunction
            ) = 0;
};

class InitializePluginHandler : public PluginHandler
{
public:

    InitializePluginHandler( MFnPlugin& pluginFn )
     : m_pluginFn( pluginFn ) {}

    MStatus handleNode(
            const MString& typeName,
            const MTypeId& typeId,
            MCreatorFunction creatorFunction,
            MInitializeFunction initFunction,
            MPxNode::Type type = MPxNode::kDependNode,
            const MString* classification = NULL
            )
    {
        return m_pluginFn.registerNode(
                typeName,
                typeId,
                creatorFunction,
                initFunction,
                type,
                classification
                );
    }

    MStatus handleCommand(
            const MString& commandName,
            MCreatorFunction creatorFunction,
            MCreateSyntaxFunction createSyntaxFunction = NULL
            )
    {
        return m_pluginFn.registerCommand(
                commandName,
                creatorFunction,
                createSyntaxFunction
                );
    }

    MStatus handleData(
            const MString& typeName,
            const MTypeId& typeId,
            MCreatorFunction creatorFunction,
            MPxData::Type type = MPxData::kData
            )
    {
        return m_pluginFn.registerData(
                typeName,
                typeId,
                creatorFunction,
                type
                );
    }

    MStatus handleControlCommand(
            const MString& commandName,
            MCreatorFunction creatorFunction
            )
    {
        return m_pluginFn.registerControlCommand(
                commandName,
                creatorFunction
                );
    }

private:

    MFnPlugin& m_pluginFn;
};


class UninitializePluginHandler : public PluginHandler
{
public:

    UninitializePluginHandler( MFnPlugin& pluginFn )
     : m_pluginFn( pluginFn ) {}

    MStatus handleNode(
            const MString&,
            const MTypeId& typeId,
            MCreatorFunction,
            MInitializeFunction,
            MPxNode::Type = MPxNode::kDependNode,
            const MString* = NULL
            )
    {
        return m_pluginFn.deregisterNode( typeId );
    }

    MStatus handleCommand(
            const MString& commandName,
            MCreatorFunction,
            MCreateSyntaxFunction = NULL
            )
    {
        return m_pluginFn.deregisterCommand( commandName );
    }

    MStatus handleData(
            const MString&,
            const MTypeId& typeId,
            MCreatorFunction,
            MPxData::Type = MPxData::kData
            )
    {
        return m_pluginFn.deregisterData( typeId );
    }

    MStatus handleControlCommand(
            const MString& commandName,
            MCreatorFunction
            )
    {
        return m_pluginFn.deregisterControlCommand( commandName );
    }

private:

    MFnPlugin& m_pluginFn;

};

#endif // PLUGINHANDLER_HH

