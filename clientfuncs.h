#include "stdafx.h"

#pragma once

typedef struct cl_clientfuncs_s
{
	int( *Initialize )( cl_enginefunc_t *, int );
	int( *HUD_Init )( void );
	int( *HUD_VidInit )( void );
	int( *HUD_Redraw )( float, int );
	int( *HUD_UpdateClientData )( client_data_t *, float );
	int( *HUD_Reset )( void );
	void( *HUD_PlayerMove )( struct playermove_s *, int );
	void( *HUD_PlayerMoveInit )( struct playermove_s * );
	char( *HUD_PlayerMoveTexture )( char * );
	void( *IN_ActivateMouse )( void );
	void( *IN_DeactivateMouse )( void );
	void( *IN_MouseEvent )( int mstate );
	void( *IN_ClearStates )( void );
	void( *IN_Accumulate )( void );
	void( *CL_CreateMove )( float, struct usercmd_s *, int );
	int( *CL_IsThirdPerson )( void );
	void( *CL_CameraOffset )( float * );
	struct kbutton_s *( *KB_Find )( const char *name );
	void( *CAM_Think )( void );
	void( *V_CalcRefdef )( struct ref_params_s *pparams );
	int( *HUD_AddEntity )( int, struct cl_entity_s *, const char * );
	void( *HUD_CreateEntities )( void );
	void( *HUD_DrawNormalTriangles )( void );
	void( *HUD_DrawTransparentTriangles )( void );
	void( *HUD_StudioEvent )( const struct mstudioevent_s *, const struct cl_entity_s * );
	void( *HUD_PostRunCmd )( struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed );
	void( *HUD_Shutdown )( void );
	void( *HUD_TxferLocalOverrides )( struct entity_state_s *, const struct clientdata_s * );
	void( *HUD_ProcessPlayerState )( struct entity_state_s *, const struct entity_state_s * );
	void( *HUD_TxferPredictionData )( struct entity_state_s *, const struct entity_state_s *, struct clientdata_s *, const struct clientdata_s *, struct weapon_data_s *, const struct weapon_data_s * );
	void( *Demo_ReadBuffer )( int, unsigned char * );
	int( *HUD_ConnectionlessPacket )( struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size );
	int( *HUD_GetHullBounds )( int hullnumber, float *mins, float *maxs );
	void( *HUD_Frame )( double time );
	int( *HUD_Key_Event )( int, int, const char * );
	void( *HUD_TempEntUpdate )( double, double, double, struct tempent_s **, struct tempent_s **, int( *Callback_AddVisibleEntity )( struct cl_entity_s *pEntity ), void( *Callback_TempEntPlaySound )( struct tempent_s *pTemp, float damp ) );
	struct cl_entity_s *( *HUD_GetUserEntity )( int index );
	int( *HUD_VoiceStatus )( int entindex, qboolean bTalking );
	int (*HUD_DirectorMessage) (unsigned char command, unsigned int firstObject, unsigned int secondObject, unsigned int flags); // HUD_DirectorEvent => HUD_DirectorMessage
	int (*HUD_GetStudioModelInterface)( int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio );
	// HUD_ChatInputPosition
	// 
	// char uk[4];
	// ClientFactory 
} cl_clientfunc_t;