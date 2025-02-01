/************************************************************************
**	D B D A O I D . H													*
**																		*
**	OLE DAO component class id definitions								*
**																		*
*************************************************************************
** Copyright (C) 1992-5 by Microsoft Corporation		 				*
**		   All Rights Reserved					 						*
************************************************************************/

/*
	All UNICODE IID_... names are the same as the ANSI IID_... name
		with a "W" appended to the end.

*/

// Type library
DEFINE_OLEGUID(LIBID_CDAO,				0x00025e01, 0, 0);

// StdObject
DEFINE_OLEGUID(IID_IDAOStdObject,		0x00025e02, 0, 0);

// StdCollection
DEFINE_OLEGUID(IID_IDAOStdCollection,	0x00025e03, 0, 0);

// DBEngine
DEFINE_OLEGUID(CLSID_CDAODBEngine,		0x00025e15, 0, 0);
DEFINE_OLEGUID(IID_IDAODBEngine,		0x00025e16, 0, 0);
DEFINE_OLEGUID(IID_IDAODBEngineW,		0x00025e17, 0, 0);
DEFINE_OLEGUID(CLSID_CDAOPrivDBEngine,	0x00025e19, 0, 0);

// Error
DEFINE_OLEGUID(IID_IDAOError,			0x00025e1d, 0, 0);
DEFINE_OLEGUID(IID_IDAOErrorW,			0x00025e1e, 0, 0);
DEFINE_OLEGUID(IID_IDAOErrors,			0x00025e1f, 0, 0);
DEFINE_OLEGUID(IID_IDAOErrorsW,			0x00025e20, 0, 0);

// Property
DEFINE_OLEGUID(IID_IDAOProperty,		0x00025e25, 0, 0);
DEFINE_OLEGUID(IID_IDAOPropertyW,		0x00025e26, 0, 0);
DEFINE_OLEGUID(IID_IDAOProperties,		0x00025e27, 0, 0);
DEFINE_OLEGUID(IID_IDAOPropertiesW,		0x00025e28, 0, 0);

// Recordset
DEFINE_OLEGUID(IID_IDAORecordset,		0x00025e2d, 0, 0);
DEFINE_OLEGUID(IID_IDAORecordsetW,		0x00025e2e, 0, 0);
DEFINE_OLEGUID(IID_IDAORecordsets,		0x00025e2f, 0, 0);
DEFINE_OLEGUID(IID_IDAORecordsetsW,		0x00025e30, 0, 0);
DEFINE_OLEGUID(IID_ICDAORecordset,		0x00025e31, 0, 0);

// Workspace
DEFINE_OLEGUID(IID_IDAOWorkspace,		0x00025e3a, 0, 0);
DEFINE_OLEGUID(IID_IDAOWorkspaceW,		0x00025e3b, 0, 0);
DEFINE_OLEGUID(IID_IDAOWorkspaces,		0x00025e3c, 0, 0);
DEFINE_OLEGUID(IID_IDAOWorkspacesW,		0x00025e3d, 0, 0);

// TableDef
DEFINE_OLEGUID(CLSID_CDAOTableDef,		0x00025e43, 0, 0);
DEFINE_OLEGUID(IID_IDAOTableDef,		0x00025e44, 0, 0);
DEFINE_OLEGUID(IID_IDAOTableDefW,		0x00025e45, 0, 0);
DEFINE_OLEGUID(IID_IDAOTableDefs,		0x00025e46, 0, 0);
DEFINE_OLEGUID(IID_IDAOTableDefsW,		0x00025e47, 0, 0);

// Field
DEFINE_OLEGUID(CLSID_CDAOField, 		0x00025e4c, 0, 0);
DEFINE_OLEGUID(IID_IDAOField,			0x00025e4d, 0, 0);
DEFINE_OLEGUID(IID_IDAOFieldW,			0x00025e4e, 0, 0);
DEFINE_OLEGUID(IID_IDAOFields,			0x00025e4f, 0, 0);
DEFINE_OLEGUID(IID_IDAOFieldsW,			0x00025e50, 0, 0);

// Index
DEFINE_OLEGUID(CLSID_CDAOIndex, 		0x00025e55, 0, 0);
DEFINE_OLEGUID(IID_IDAOIndex,			0x00025e56, 0, 0);
DEFINE_OLEGUID(IID_IDAOIndexW,			0x00025ed7, 0, 0);
DEFINE_OLEGUID(IID_IDAOIndexes,			0x00025e58, 0, 0);
DEFINE_OLEGUID(IID_IDAOIndexesW,		0x00025e59, 0, 0);
DEFINE_OLEGUID(IID_IDAOIndexFields,		0x00025e5a, 0, 0);
DEFINE_OLEGUID(IID_IDAOIndexFieldsW,	0x00025e5b, 0, 0);

// Group
DEFINE_OLEGUID(CLSID_CDAOGroup, 		0x00025e5f, 0, 0);
DEFINE_OLEGUID(IID_IDAOGroup,			0x00025e60, 0, 0);
DEFINE_OLEGUID(IID_IDAOGroupW,			0x00025e61, 0, 0);
DEFINE_OLEGUID(IID_IDAOGroups,			0x00025e62, 0, 0);
DEFINE_OLEGUID(IID_IDAOGroupsW,			0x00025e63, 0, 0);

// User
DEFINE_OLEGUID(CLSID_CDAOUser,			0x00025e68, 0, 0);
DEFINE_OLEGUID(IID_IDAOUser,			0x00025e69, 0, 0);
DEFINE_OLEGUID(IID_IDAOUserW,			0x00025e6a, 0, 0);
DEFINE_OLEGUID(IID_IDAOUsers,			0x00025e6b, 0, 0);
DEFINE_OLEGUID(IID_IDAOUsersW,			0x00025e6c, 0, 0);

// Database
DEFINE_OLEGUID(IID_IDAODatabase,		0x00025e71, 0, 0);
DEFINE_OLEGUID(IID_IDAODatabaseW,		0x00025e72, 0, 0);
DEFINE_OLEGUID(IID_IDAODatabases,		0x00025e73, 0, 0);
DEFINE_OLEGUID(IID_IDAODatabasesW,		0x00025e74, 0, 0);

// QueryDef
DEFINE_OLEGUID(CLSID_CDAOQueryDef,		0x00025e7a, 0, 0);
DEFINE_OLEGUID(IID_IDAOQueryDef,		0x00025e7b, 0, 0);
DEFINE_OLEGUID(IID_IDAOQueryDefW,		0x00025e7c, 0, 0);
DEFINE_OLEGUID(IID_IDAOQueryDefs,		0x00025e7d, 0, 0);
DEFINE_OLEGUID(IID_IDAOQueryDefsW,		0x00025e7e, 0, 0);

// Parameter
DEFINE_OLEGUID(IID_IDAOParameter,		0x00025e83, 0, 0);
DEFINE_OLEGUID(IID_IDAOParameterW,		0x00025e84, 0, 0);
DEFINE_OLEGUID(IID_IDAOParameters,		0x00025e85, 0, 0);
DEFINE_OLEGUID(IID_IDAOParametersW,		0x00025e86, 0, 0);

// Relation
DEFINE_OLEGUID(CLSID_CDAORelation,		0x00025e8b, 0, 0);
DEFINE_OLEGUID(IID_IDAORelation,		0x00025e8c, 0, 0);
DEFINE_OLEGUID(IID_IDAORelationW,		0x00025e8d, 0, 0);
DEFINE_OLEGUID(IID_IDAORelations,		0x00025e8e, 0, 0);
DEFINE_OLEGUID(IID_IDAORelationsW,		0x00025e8f, 0, 0);

// Container
DEFINE_OLEGUID(IID_IDAOContainer,		0x00025e94, 0, 0);
DEFINE_OLEGUID(IID_IDAOContainerW,		0x00025e95, 0, 0);
DEFINE_OLEGUID(IID_IDAOContainers,		0x00025e96, 0, 0);
DEFINE_OLEGUID(IID_IDAOContainersW,		0x00025e97, 0, 0);

// Document
DEFINE_OLEGUID(IID_IDAODocument,		0x00025e9c, 0, 0);
DEFINE_OLEGUID(IID_IDAODocumentW,		0x00025e9d, 0, 0);
DEFINE_OLEGUID(IID_IDAODocuments,		0x00025e9e, 0, 0);
DEFINE_OLEGUID(IID_IDAODocumentsW,		0x00025e9f, 0, 0);


