#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 8

char* pawn_move(char board[SIZE][SIZE], int r, int c, int new_r, int new_c, bool user);
char* knight_move(char board[SIZE][SIZE], int r, int c, int new_r, int new_c, bool user);
char* king_move(char board[SIZE][SIZE], int r, int c, int new_r, int new_c, bool user);

void print_board(char board[SIZE][SIZE]) {
    printf("   ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", i);
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d  ", i);
        for (int j = 0; j < SIZE; j++)
            printf("%c ", board[i][j]);
        printf("\n");
    }
    return;
}

int get_position(int *r, int *c) {
    int success = scanf("%d %d", r, c);
    if (success == 2) return 1;
    success = scanf("%d,%d", r, c);
    if (success == 2) return 1;
    success = scanf("%d-%d", r, c);
    if (success == 2) return 1;
    success = scanf("(%d,%d)", r, c);
    if (success == 2) return 1;
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    return 0;
}

int main() {
    char board[SIZE][SIZE] = {
        "RNBQKBNR",
        "PPPPPPPP",
        "........",
        "........",
        "........",
        "........",
        "pppppppp",
        "rnbqkbnr"
    };

    print_board(board);

    bool user = true;
    char *moved_piece;
    int r, c, new_r, new_c;

    while (1) {
        printf("User %d: Please choose a piece type to move (P/N/K):\n", user ? 1 : 2);
        char piece_type;
        scanf(" %c", &piece_type);

        printf("User %d: Please choose the piece position (provide r and c):\n", user ? 1 : 2);
        while (1) {
            if (get_position(&r, &c))
                break;
            printf("Error. Could not read input, try again.\n");
        }
        printf("User %d: Please provide the destination position (provide new_r and new_c):\n", user ? 1 : 2);
        while (1) {
            if (get_position(&new_r, &new_c))
                break;
            printf("Error. Could not read input, try again.\n");
        }

        int success = 0;

        if (piece_type == 'P' || piece_type == 'p') {
            moved_piece = pawn_move(board, r, c, new_r, new_c, user);
        } else if (piece_type == 'N' || piece_type == 'n') {
            moved_piece = knight_move(board, r, c, new_r, new_c, user);
        } else if (piece_type == 'K' || piece_type == 'k') {
            moved_piece = king_move(board, r, c, new_r, new_c, user);
        }

        if (moved_piece) {
            printf("%c moved successfully!\n", piece_type);
            success = 1;
        }

        if (success) {
            print_board(board);
            user = !user;
        } else {
            printf("Error. Could not make move, invalid position or piece. Please try again.\n\n");
        }
    }

    return 0;
}

char* pawn_move(char board[SIZE][SIZE], int r, int c, int new_r, int new_c, bool user) {
    char piece = board[r][c];
    char pawn_piece = user ? 'P' : 'p';
    int direction = user ? 1 : -1;

    if (piece != pawn_piece) {
        return NULL;
    }

    if (new_r == r + direction && new_c == c && board[new_r][new_c] == '.') {
        board[new_r][new_c] = piece;
        board[r][c] = '.';
        return &board[new_r][new_c];
    }

    if ((r == 1 && user) || (r == 6 && !user)) {
        if (new_r == r + 2 * direction && new_c == c && board[new_r][new_c] == '.' && board[r + direction][c] == '.') {
            board[new_r][new_c] = piece;
            board[r][c] = '.';
            return &board[new_r][new_c];
        }
    }

    if (new_r == r + direction && (new_c == c + 1 || new_c == c - 1)) {
        char dest_piece = board[new_r][new_c];
        if (dest_piece != '.' && 
            ((user && dest_piece >= 'a' && dest_piece <= 'z') || 
            (!user && dest_piece >= 'A' && dest_piece <= 'Z'))) {
            board[new_r][new_c] = piece;
            board[r][c] = '.';
            return &board[new_r][new_c];
        }
    }

    return NULL;
}

char* knight_move(char board[SIZE][SIZE], int r, int c, int new_r, int new_c, bool user) {
    char piece = board[r][c];
    char knight_piece = user ? 'N' : 'n';

    if (piece != knight_piece)
        return NULL;

    if (!((abs(new_r - r) == 2 && abs(new_c - c) == 1) || (abs(new_r - r) == 1 && abs(new_c - c) == 2)))
        return NULL;

    char dest_piece = board[new_r][new_c];
    if (user && (dest_piece >= 'A' && dest_piece <= 'Z'))
        return NULL;
    if (!user && (dest_piece >= 'a' && dest_piece <= 'z'))
        return NULL;

    board[new_r][new_c] = piece;
    board[r][c] = '.';

    return &board[new_r][new_c];
}

char* king_move(char board[SIZE][SIZE], int r, int c, int new_r, int new_c, bool user) {
    char piece = board[r][c];
    char king_piece = user ? 'K' : 'k';

    if (piece != king_piece)
        return NULL;

    if (abs(new_r - r) > 1 || abs(new_c - c) > 1)
        return NULL;

    char dest_piece = board[new_r][new_c];
    if (user && (dest_piece >= 'A' && dest_piece <= 'Z'))
        return NULL;
    if (!user && (dest_piece >= 'a' && dest_piece <= 'z'))
        return NULL;

    board[new_r][new_c] = piece;
    board[r][c] = '.';

    return &board[new_r][new_c];
}
