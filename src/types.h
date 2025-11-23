#pragma once

#include "util.h"




struct	Type
{
	char							*name;
	struct Type						*parent;
	int								size;
	Repository_t					*repo;
};

typedef								struct	Type					Type_t;

typedef								struct	Repository				Repository_t;


#define																			\
type_var( name )					concat3	( name, _, type )

#define																			\
DECL_TYPE( type, parent )			extern	Type_t type_var(type)

#define																			\
DEFINE_TYPE( type, parent_type )	Type_t										\
									type_var(type)	=	{						\
										.name		=	str ( type ),			\
										.parent		=	NULL,					\
										.size		=	sizeof ( type ),		\
										.repo		=	NULL					\
									}




DECL_TYPE						(	Type_t,				NULL		);

DECL_TYPE						(	Vec2_t,				Type_t		);

DECL_TYPE						(	Vec3_t,				Type_t		);

DECL_TYPE						(	Line_t,				Type_t		);

DECL_TYPE						(	Point2d_t,			Type_t		);

DECL_TYPE						(	Point3d_t,			Type_t		);

DECL_TYPE						(	Triangle2d_t,		Type_t		);

DECL_TYPE						(	Triangle3d_t,		Type_t		);

DECL_TYPE						(	Face_t,				Type_t		);

DECL_TYPE						(	Mesh_t,				Type_t		);

DECL_TYPE						(	Renderer_t,			Type_t		);

DECL_TYPE						(	Window_t,			Type_t		);

DECL_TYPE						(	Texture_t,			Type_t		);

DECL_TYPE						(	Choreographer_t,	Type_t		);



Type_t*							get_type					(	Type_t*		type	)
{
	RETURN					(	type	);
}

#define							for_each_type(type)				for	(	type = 0; type < TYPE_MAX; type++	)



