/*
    Written 2006 lihu

    Copyright 2006 lihu.
    This software may be used and distributed according to the terms of the GNU General Public License,
    incorporated herein by reference.

    The author may be reached as lilachue@163.com .
    */

#ifndef _XINI_H_
#define _XINI_H_

#ifdef __cplusplus
extern "C" {
#endif

#define XINI_NODE_DATA_LEN	256

#define XINI_NTYPE_SECTION	1
#define XINI_NTYPE_KEY	2
#define XINI_NTYPE_DATA	3
#define XINI_NTYPE_REMARK	4

    typedef struct xini_node_s
    {

        /*
         * node type, section, key, remark
         * but this field is reserved for future
         */
        int ntype;

        char data[XINI_NODE_DATA_LEN];

        /*
         * double linked list, for both section node and key node.
         */
        struct xini_node_s *next, *prev;

        /*
         * key_head & key_tail used to link key list
         * parent & child used to link key and it's value node
         */
        union
        {
            struct xini_node_s *parent, *key_head;
        } u1;
        union
        {
            struct xini_node_s *child, *key_tail;
        } u2;
    }XINI_NODE;

#define XINI_FILE_LEN	32
    typedef struct xini_s
    {
        /* MEMBERS */
        /* current loaded data file */
        char *file;

        /* section list */
        struct xini_node_s *section_head, *section_tail;

        /* section list, for section cursor */
        struct xini_node_s *section_cursor;
        /* reserved for travering list */
        struct xini_node_s *section_trav_tmp;

        /* key list, for key cursor */
        struct xini_node_s *key_cursor;
        /* reserved for travering list */
        struct xini_node_s *key_trav_tmp;

        /* DEBUG PATH */
        int dbg_mem_alloc_cnt, dbg_mem_free_cnt;

        /* METHODS */
        /* Load data from file f */
        int(*load)(struct xini_s *h, char *f);
        /* Reload data */
        int(*reload)(struct xini_s *h);
        /* Save data */
        int(*save)(struct xini_s *h);
        /* Save to another file */
        int(*save_as)(struct xini_s *h, char *f);
        /* Dispose allocated memories */
        int(*dispose)(struct xini_s *h);

        /*section operation*/
        int(*section_create)(struct xini_s *h, char *s);
        int(*section_remove)(struct xini_s *h, char *s);
        int(*section_modify)(struct xini_s *h, char *s, char *n);

        /*key operation*/
        int(*key_create)(struct xini_s *h, char *s, char *k);
        int(*key_remove)(struct xini_s *h, char *s, char *k);
        int(*key_modify)(struct xini_s *h, char *s, char *k, char *d);

        /*data operation*/
        int(*data_create)(struct xini_s *h, char *s, char *k, char *d);
        int(*data_remove)(struct xini_s *h, char *s, char *k, char *d);
        int(*data_modify)(struct xini_s *h, char *s, char *k, char *d, char *nd);


        /* Section cursor operations */
        int(*section_cursor_eof)(struct xini_s *h);
        int(*section_cursor_set)(struct xini_s *h, char *s);
        int(*section_cursor_move_first)(struct xini_s *h);
        int(*section_cursor_move_next)(struct xini_s *h);
        int(*section_cursor_move_prev)(struct xini_s *h);
        int(*section_cursor_move_last)(struct xini_s *h);
        char *(*section_cursor_data)(struct xini_s *h);

        /* Key cursor operations */
        int(*key_cursor_eof)(struct xini_s *h);
        int(*key_cursor_set)(struct xini_s *h, char *k);
        int(*key_cursor_move_first)(struct xini_s *h);
        int(*key_cursor_move_next)(struct xini_s *h);
        int(*key_cursor_move_prev)(struct xini_s *h);
        int(*key_cursor_move_last)(struct xini_s *h);
        char *(*key_cursor_data)(struct xini_s *h);

        char * (*ptr_data_get)(struct xini_s *h, char *s, char *k);

    }XINI;

    extern int xini_initial(XINI *h);
    extern int xini_destroy(XINI *h);

#define eq_str(a,b)	(strcmp(a,b)==0)
#define os_strncpy	strncpy
#define os_strcpy	strcpy
#define os_strcmp	strcmp
#define os_memset	memset
#define os_strlen		strlen

    /* error code define */
#define XE_BASE			-9000
#define XE_CODE(e)	( XE_BASE - e )

#define XE_NONE			XE_CODE(XE_BASE)
#define XE_ERROR		XE_CODE( 1 )
#define XE_MEM			XE_CODE( 2 )
#define XE_FILE			XE_CODE( 3 )
#define XE_FMT			XE_CODE( 4 )
#define XE_EXIST			XE_CODE( 5 )
#define XE_NEXIST		XE_CODE( 6 )
#define XE_NCURSOR		XE_CODE( 7 )
#define XE_NSCURSOR		XE_CODE( 8 ) /* no section cursor */
#define XE_NKCURSOR		XE_CODE( 8 ) /* no key cursor */

#ifdef __cplusplus
}
#endif

#endif

