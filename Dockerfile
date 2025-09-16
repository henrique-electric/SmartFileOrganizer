FROM archlinux:latest

RUN pacman -Syyu --noconfirm && pacman -S sudo libarchive cmake base-devel libsndfile zsh git --noconfirm

RUN echo "dev ALL = (ALL:ALL) ALL" > /etc/sudoers

RUN useradd -m dev 

RUN printf "dev145\ndev145\n" | passwd dev

USER dev
WORKDIR /home/dev/SFO/
RUN printf "\ndev145\dev145" | sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

CMD ["zsh"]
