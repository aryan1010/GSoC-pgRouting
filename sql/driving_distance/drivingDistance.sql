/*PGR-GNU*****************************************************************
FILE: drivingDistance.sql

Copyright (c) 2015 Celia Virginia Vergara Castillo
Mail: vicky AT erosion.dev

Copyright (c) 2023 Aryan Gupta
Mail: guptaaryan1010 AT gmail.com

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

-- MULTIPLE
--v3.6
CREATE FUNCTION pgr_drivingDistance(
    TEXT,     -- edges_sql (required)
    ANYARRAY, -- from_vids (required)
    FLOAT,    -- distance (required)

    directed BOOLEAN DEFAULT TRUE,
    equicost BOOLEAN DEFAULT FALSE,

    OUT seq INTEGER,
    OUT depth  BIGINT,
    OUT start_vid  BIGINT,
    OUT node BIGINT,
    OUT edge BIGINT,
    OUT cost FLOAT,
    OUT agg_cost FLOAT)
RETURNS SETOF RECORD AS
$BODY$
    SELECT *
    FROM _pgr_v4drivingDistance(_pgr_get_statement($1), $2, $3, $4, $5);
$BODY$
LANGUAGE SQL VOLATILE STRICT
COST 100
ROWS 1000;


-- SINGLE
--v3.6
CREATE FUNCTION pgr_drivingDistance(
    TEXT,   -- edges_sql (required)
    BIGINT, -- from_vid (requierd)
    FLOAT,  -- distance (required)

    directed BOOLEAN DEFAULT TRUE,

    OUT seq INTEGER,
    OUT depth  BIGINT,
    OUT start_vid  BIGINT,
    OUT node BIGINT,
    OUT edge BIGINT,
    OUT cost FLOAT,
    OUT agg_cost FLOAT)
RETURNS SETOF RECORD AS
$BODY$
    SELECT *
    FROM _pgr_v4drivingDistance(_pgr_get_statement($1), ARRAY[$2]::BIGINT[], $3, $4, false);
$BODY$
LANGUAGE SQL VOLATILE STRICT
COST 100
ROWS 1000;

-- COMMENTS

COMMENT ON FUNCTION pgr_drivingDistance(TEXT, BIGINT, FLOAT, BOOLEAN)
IS 'pgr_v4drivingDistance(Single_vertex)
- Parameters:
   - Edges SQL with columns: id, source, target, cost [,reverse_cost]
   - From vertex identifier
   - Distance from vertex identifier
- Optional Parameters
   - directed := true
- Documentation:
   - ${PROJECT_DOC_LINK}/pgr_v4drivingDistance.html
';

COMMENT ON FUNCTION pgr_drivingDistance(TEXT, ANYARRAY, FLOAT, BOOLEAN, BOOLEAN)
IS 'pgr_v4drivingDistance(Multiple vertices)
- Parameters:
   - Edges SQL with columns: id, source, target, cost [,reverse_cost]
   - From ARRAY[vertices identifiers]
   - Distance from vertices identifiers
- Optional Parameters
   - directed := true
   - equicost := false
- Documentation:
   - ${PROJECT_DOC_LINK}/pgr_v4drivingDistance.html
';


