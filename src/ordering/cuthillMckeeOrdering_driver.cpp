/*PGR-GNU*****************************************************************
File: cuthillMckeeOrdering_driver.cpp
Generated with Template by:
Copyright (c) 2022 pgRouting developers
Mail: project@pgrouting.org
Function's developer:
Copyright (c) 2022 Shobhit Chaurasia
Mail: 000shobhitchaurasia at gmail.com
------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

********************************************************************PGR-GNU*/

#include "drivers/ordering/cuthillMckeeOrdering_driver.h"

#include <sstream>
#include <vector>
#include <algorithm>
#include <string>

#include "cpp_common/pgr_alloc.hpp"
#include "cpp_common/pgr_assert.h"
#include "c_types/ii_t_rt.h"

#include "ordering/cuthillMckeeOrdering.hpp"

#if 0
/* TODO To_be_created Same type as the return type of fn_cuthillMckeeOrdering*/
static
std::vector <II_t_rt>
cuthillMckeeOrdering(pgrouting::UndirectedGraph &graph, int64_t start_vid) {
    pgrouting::functions::CuthillMckeeOrdering fn;
    auto results = fn.cuthillMckeeOrdering(graph, start_vid);
#if 0    
    log << fn.get_log();
#endif
    return results;
}
#endif

#if 1
template <class G>
std::vector <II_t_rt>
cuthillMckeeOrdering(G &graph, int64_t start_vid) {
    pgrouting::functions::CuthillMckeeOrdering <G> fn_cuthillMckeeOrdering;
    auto results = fn_cuthillMckeeOrdering.cuthillMckeeOrdering(graph, start_vid);
    return results;
}
#endif

void do_cuthillMckeeOrdering(
    Edge_t *data_edges,
    size_t total_edges,

    int64_t start_vid,

    II_t_rt **return_tuples,
    size_t *return_count,

    char **log_msg,
    char **notice_msg,
    char **err_msg) {
    std::ostringstream log;
    std::ostringstream err;
    std::ostringstream notice;
    try {
        pgassert(!(*log_msg));
        pgassert(!(*notice_msg));
        pgassert(!(*err_msg));
        pgassert(!(*return_tuples));
        pgassert(*return_count == 0);

        graphType gType = UNDIRECTED;

        pgrouting::UndirectedGraph undigraph(gType);
        undigraph.insert_edges(data_edges, total_edges);
        auto results = cuthillMckeeOrdering(undigraph, start_vid);  // might cause error bcz of type
        // pgrouting::functions::CuthillMckeeOrdering fn;
        // auto results = fn.cuthillMckeeOrdering(undigraph, start_vid);
        // log << fn.get_log();

        auto count = results.size();

        if (count == 0) {
            (*return_tuples) = NULL;
            (*return_count) = 0; 
            notice << "No results found";
            *log_msg = pgr_msg(log.str().c_str());
            return;
        }

        (*return_tuples) = pgr_alloc(count, (*return_tuples));
        for (size_t i = 0; i < count; i++) {
            *((*return_tuples) + i) = results[i];
        }
        (*return_count) = count;

        pgassert(*err_msg == NULL);
        *log_msg = log.str().empty() ?
        *log_msg :
        pgr_msg(log.str().c_str());
        *notice_msg = notice.str().empty() ?
        *notice_msg :
        pgr_msg(notice.str().c_str());
    } catch (AssertFailedException &except) {
        (*return_tuples) = pgr_free(*return_tuples);
        (*return_count) = 0;
        err << except.what();
        *err_msg = pgr_msg(err.str().c_str());
        *log_msg = pgr_msg(log.str().c_str());
    } catch (std::exception &except) {
        (*return_tuples) = pgr_free(*return_tuples);
        (*return_count) = 0;
        err << except.what();
        *err_msg = pgr_msg(err.str().c_str());
        *log_msg = pgr_msg(log.str().c_str());
    } catch (...) {
        (*return_tuples) = pgr_free(*return_tuples);
        (*return_count) = 0;
        err << "Caught unknown exception!";
        *err_msg = pgr_msg(err.str().c_str());
        *log_msg = pgr_msg(log.str().c_str());
    }
}
