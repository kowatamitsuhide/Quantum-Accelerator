/**
 *  MemoryInfoSet.h
 *
 *  Copyright(c) Live2D Inc. All rights reserved.
 *  [[ CONFIDENTIAL ]]
 */

#pragma once


#ifndef __SKIP_DOC__

#include "../../Live2D.h"

#ifndef NULL
#  define NULL    0
#endif


//--------- LIVE2D NAMESPACE ------------
namespace live2d 
{

	class AMemoryHolder ;
	class MemoryParam ;
	class MemoryInfo ;


	//******************************************************
	class MemoryInfoSet // �?���?��用なので管�?�?
	{
		friend class UtMemory ;
		friend class MemoryInfo ;
	public:
		MemoryInfoSet(const char* setName);
		~MemoryInfoSet(void);

		void dump(const char* message = NULL ) ;
		void dumpList( MemoryInfo *info ) ;

		void addMemoryInfo( void* ptr , MemoryParam* owner , l2d_size_t size , const char* filename , int lineno ) ;
		void removeMemoryInfo( void* ptr ) ;

		int getMallocTotal(){ return mallocTotal ; }	// mallocの回数をカウン�?
		int	getRestCount(){ return restCount ; }		// 確保して�?��ポインタ数をカウン�?(mallocで++ , freeで--)
		int	getTotalMemory(){ return totalMemory ; }	// 累積メモリ

		int getCurMemory(){ return curMemory ; }		// 現在のメモリ
		int getPeakMemory(){ return peakMemory ; }		// �?��時�?メモリ

	private:
		const char*		setName ;

		int				mallocTotal ;			// mallocの回数をカウン�?
		int				restCount ;				// 確保して�?��ポインタ数をカウン�?(mallocで++ , freeで--)
		int				totalMemory ;			// 累積メモリ
		int				curMemory ;				// 現在のメモリ
		int				peakMemory ;			// �?��時�?メモリ

		MemoryInfo*		usingMemoryInfo ;		// 使用中メモリ�??の先�??��?結リスト�?
		MemoryInfo*		lastUsingMemoryInfo ;	// 使用中メモリ�??リスト�?�?��尾?��?結リスト�?
		MemoryInfo*		freeMemoryInfo ;		// 解放済みメモリ�??リスト（�?結リスト�?
		MemoryInfo*		lastFreeMemoryInfo ;	// 解放済みメモリ�??リスト�?�?��尾?��?結リスト�?
	};
}
//--------- LIVE2D NAMESPACE ------------

#endif // __SKIP_DOC__

