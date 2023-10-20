# Philosophers

Philosophes est un projet de la partie obligatoire du cursus. Il est uniquement réalisé en C et l'objectif principal était de comprendre comment fonctionnent les threads en langage C et de les utiliser pour résoudre un problème logique. La simulation s'arrêtera si tous les philosophes ont suffisamment mangé ou si un philosophe meurt.


## Le probleme du Dîner des philosophes

Le problème bien établi des philosophes de la restauration. Il est configuré comme suit et démontré dans l’illustration ci-dessus :

- Un ou plusieurs philosophes sont assis à une table ronde, au centre de laquelle se trouve un bol de spaghetti.
- Il y a autant de fourchettes que de philosophes, une entre chaque philosophe. Une fourchette ne peut être utilisée que par les philosophes assis juste à côté.
- Les philosophes ne peuvent manger que lorsqu’ils tiennent une fourchette dans chaque main. Une fois qu'ils ont fini de manger, ils déposent les fourchettes.
- Les philosophes alternent entre manger, dormir et bien sûr réfléchir. Ils ne peuvent pas faire deux choses à la fois.
- Si un philosophe reste trop longtemps sans manger, il mourra de faim.
- Les philosophes ne peuvent pas communiquer.

Le but est, à terme, d’éviter que les philosophes ne meurent, c’est-à-dire d’éviter que le programme ne s’enlise, dans lequel aucun progrès n’est plus possible.

De plus, chaque philosophe sera son propre processus ou fil conducteur, et chaque foutchette aura son propre mutex.


## threads et des mutex

Le cœur de ce projet se résume à aborder l’exécution parallèle, qui consiste essentiellement à créer plusieurs flux de travail ou processus simultanés. Un flux de travail unique est appelé un thread.

Un mutex, également appelé verrou, est un mécanisme utilisé lorsqu'il existe plusieurs threads pour limiter l'accès à une ressource. Il garantit que plusieurs threads ne peuvent pas écrire ou lire à partir d'une ressource en même temps, garantissant ainsi qu'un thread ne lit pas une ressource pendant qu'un autre la modifie.

Les deux sont contrôlés via les fonctions de la bibliothèque pthread.h.


## Input attendue

Le programme s'exécute avec les arguments suivants :

./philo num_of_philo time_to_die time_to_eat time_to_sleep [num_eat]

Explication des arguments :

|num_of_philo |Le nombre de philosophes (et de fourchettes).|
|:-----:| :-----|
|time_to_die* |Combien de temps faut-il au philosophe pour mourir sans manger. Mesuré par le temps écoulé depuis le début de leur dernier repas ou le début de la simulation.|
|time_to_eat* |Le temps qu'un philosophe passe à manger.|
|time_to_sleep* |La durée pendant laquelle un philosophe passe à dormir.|
|num_eat (optionel)|Le nombre de fois que chaque philosophe doit manger avant la fin de la simulation. Si cela n'est pas précisé, la simulation ne s'arrête qu'à la mort d'un philosophe.|

*mesuré en millisecondes


## Exemple d'Output

![Exemple d'Output](https://github.com/Maxime2i/Philosophers/assets/43725047/03a5c797-c3d8-4dee-85f7-0fec0929e9ad)
