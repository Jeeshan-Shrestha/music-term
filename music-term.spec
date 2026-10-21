Name: music-term
Version: 1.0.0
Release:        %autorelease
Summary: Music Downloader from terminal

License: MIT
URL: https://github.com/Jeeshan-Shrestha/music-term
Source0: %{url}/archive/v%{version}/%{name}-%{version}.tar.gz 

BuildRequires: gcc
Requires: yt-dlp

%description
A simple music downloader that can be used from the terminal.


%prep
%autosetup


%build
gcc %{optflags} music.c -o music-term


%install
install -Dm755 music-term %{buildroot}%{_bindir}/music-term



