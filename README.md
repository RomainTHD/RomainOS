# RomainOS

Refonte intégrale !

Ici on va s'intéresser à de l'EFI fait maison.

Du coup, c'est toujours une idée à la con, from scratch, en 64 bits, à base de C++, mais sans assembleur (ouf).

La version old-school legacy-BIOS est bien sûr toujours dispo dans une branche parallèle, d'ailleurs peut-être que je continuerai de la développer.

### Comment faire

Déjà, il nous faut un disque, en exécutant `dd if=/dev/zero of=drive.hdd bs=512 count=524288` (250 Mo, le minimum pour une partition FAT32).

Ensuite, monter le disque avec l'outil de votre choix (sinon [OSFMount](https://www.osforensics.com/tools/mount-disk-images.html) fera l'affaire),
en lecture / écriture directe, émulation physique du disque, disque brut.

Puis, depuis un gestionnaire de partitions, créer une table GPT (pas MBR, on est en UEFI maintenant), puis une partition FAT32.

Depuis l'explorateur de fichiers, créer `EFI/Boot/` et y glisser le fichier `BOOTX64.EFI` (compilé justement dans ce projet).

Puis, magie, VirtualBox en mode EFI et tout marche.

(Vachement plus direct que via le BIOS wow).
