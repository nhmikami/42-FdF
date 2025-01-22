#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    void *mlx = mlx_init();
    if (!mlx)
    {
        printf("Error: Unable to initialize MLX.\n");
        return (1);
    }
    printf("MLX initialized successfully!\n");
    return (0);
}
