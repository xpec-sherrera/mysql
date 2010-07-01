/* Copyright (C) 2008-2009 Sun Microsystems, Inc

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; version 2 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <my_pthread.h>
#include <sql_priv.h>
#include <my_global.h>
#include <pfs_instr_class.h>
#include <pfs_global.h>
#include <tap.h>

#include "stub_pfs_global.h"

void test_oom()
{
  int rc;

  rc= init_sync_class(1000, 0, 0);
  ok(rc == 1, "oom (mutex)");
  rc= init_sync_class(0, 1000, 0);
  ok(rc == 1, "oom (rwlock)");
  rc= init_sync_class(0, 0, 1000);
  ok(rc == 1, "oom (cond)");
  rc= init_thread_class(1000);
  ok(rc == 1, "oom (thread)");
  rc= init_file_class(1000);
  ok(rc == 1, "oom (file)");
  rc= init_table_share(1000);
  ok(rc == 1, "oom (cond)");

  cleanup_sync_class();
  cleanup_thread_class();
  cleanup_file_class();
  cleanup_table_share();
}

void do_all_tests()
{
  test_oom();
}

int main(int, char **)
{
  plan(6);
  MY_INIT("pfs_instr_info-oom-t");
  do_all_tests();
  return 0;
}
