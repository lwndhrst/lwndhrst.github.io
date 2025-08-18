#include "grid.h"

#include <stdlib.h>
#include <string.h>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define clamp(val, lo, hi) (max(lo, min(val, hi)))

GridKey
grid_get_key(Grid *grid, double x, double y, double z)
{
    x = clamp(x, 0, grid->x_max);
    y = clamp(y, 0, grid->y_max);
    z = clamp(z, 0, grid->z_max);

    size_t i = x / grid->cell_size;
    size_t j = y / grid->cell_size;
    size_t k = z / grid->cell_size;

    return (GridKey){i, j, k};
}

GridCell *
grid_get_cell(Grid *grid, GridKey key)
{
    size_t idx = key.i +
                 key.j * grid->num_cells_i +
                 key.k * grid->num_cells_i * grid->num_cells_j;

    return &grid->cells[idx];
}

void
grid_init(Grid *grid,
          double x_max,
          double y_max,
          double z_max,
          double cell_size,
          size_t num_items)
{
    grid->x_max = x_max;
    grid->y_max = y_max;
    grid->z_max = z_max;

    grid->cell_size = cell_size;

    grid->num_nodes = num_items;
    grid->nodes = malloc(grid->num_nodes * sizeof(GridCellNode));
    grid->nodes_top = grid->nodes;

    grid->num_cells_i = (size_t)(x_max / cell_size) + 1;
    grid->num_cells_j = (size_t)(y_max / cell_size) + 1;
    grid->num_cells_k = (size_t)(z_max / cell_size) + 1;
    grid->num_cells = grid->num_cells_i * grid->num_cells_j * grid->num_cells_k;
    grid->cells = malloc(grid->num_cells * sizeof(GridCell));
    memset(grid->cells, 0, grid->num_cells * sizeof(GridCell));
}

void
grid_destroy(Grid *grid)
{
    free(grid->cells);
    free(grid->nodes);
}

void
grid_insert(Grid *grid,
            void *data,
            double x,
            double y,
            double z)
{
    GridKey key = grid_get_key(grid, x, y, z);
    GridCell *cell = grid_get_cell(grid, key);

    GridCellNode *node = grid->nodes_top;
    node->data = data;
    node->next = cell->head;
    ++grid->nodes_top;

    cell->head = node;
    if (cell->head == NULL) // If cell was empty
    {
        cell->tail = node;
    }
}

void
grid_clear(Grid *grid)
{
    // Reset stack pointer, no need to actually clear this
    grid->nodes_top = grid->nodes;

    // Zero all cells
    memset(grid->cells, 0, grid->num_cells * sizeof(GridCell));
}
