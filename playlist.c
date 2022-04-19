#include <stdio.h>
#include <stdlib.h>

typedef struct Song {
	char artist[20];
	char title[30];
} Song;

typedef struct Playlist {
	int no_of_songs;
	Song songs[10];
}Playlist;

void addSong(Playlist* playlist)
{
	playlist->no_of_songs = 0;
	for (int i = 0; i < 3; i++) {
		printf("%d¹øÂ° °î ÀÔ·Â\n", i + 1);
		printf("* Artist : ");
		gets(playlist->songs[i].artist);
		printf("* Title : ");
		gets(playlist->songs[i].title);
		playlist->no_of_songs++;
	}
}

void showPlaylist(Playlist* playlist)
{

	printf("No\tArtist\t\tTitle\n");
	printf("==\t======\t\t=====\n");

	for (int i = 0; i < playlist->no_of_songs; i++) {
		printf("%2d\t%s\t\t%s\n", i + 1, playlist->songs[i].artist, playlist->songs[i].title);
	}

	printf("A total number of songs in the list : %d\n", playlist->no_of_songs);
}

int main()
{
	Playlist playlist;

	addSong(&playlist);
	showPlaylist(&playlist);

	return 0;
}