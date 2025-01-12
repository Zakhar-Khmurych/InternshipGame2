#pragma once
#include "Player.h"
#include "Grid.h"

class RoundManager
{
public:
	RoundManager() {

	};

    void RunRound(Player& p1, Player& p2, Grid& grid) {
        p1.GiveCoin(1);
        p2.GiveCoin(1);
	};

};






/*
using Model;

namespace Controller;

public class RoundManager
{
    public void RunRound(Player p1, Player p2, Grid grid)
    {

        // Перевіряємо наявність некромантів

        // Роздаємо монети обом гравцям
        p1.GiveCoin(1);
        p2.GiveCoin(1);
        Console.WriteLine($"Coins given to {p1.Name} and {p2.Name}");

        p1.SpawnCreature(grid);
        p2.SpawnCreature(grid);

        grid.UpdateInitiativeOnGridLevel();
        Console.WriteLine("grid updtaed");

        var allCreatures = grid.GetAllCreatures();
        Console.WriteLine($"Total creatures on the grid: {allCreatures.Count}");
        var initiativeQueue = new PriorityQueue<Creature, int>();
        EnqueueCreaturesToInitiativeQueue(allCreatures, initiativeQueue);
        Console.WriteLine("initiative rolled");

        while (initiativeQueue.Count > 0)
        {
            var creature = initiativeQueue.Dequeue();
            Console.WriteLine($"Queue formed for {creature.GetType().Name} with initiative {creature.Initiative}");
            //Console.WriteLine($"Queue formed for {creature.GetType().Name}");
            var turnManager = new TurnManager(creature);

            while (!turnManager.TurnFinished)
            {
                var key = Console.ReadKey(true).Key;
                switch (key)
                {
                    case ConsoleKey.Q:
                        Console.WriteLine("strike! //need to get creature target. Will do later");
                        turnManager.PlayTurn();
                        RemoveDeadCreatures(grid.BringOutYourDead());
                        break;
                    case ConsoleKey.E:
                        Console.WriteLine("moving");
                        turnManager.PlayTurn(grid);
                        break;
                    case ConsoleKey.W:
                        Console.WriteLine("skipped");
                        turnManager.PlayTurn();
                        break;
                }
            }
        }

        void RemoveDeadCreatures(List<long> recently_dead)
        {
            // Видаляємо мертвих істот з активних списків
            p1.ActiveCreaturesByID.RemoveAll(id => recently_dead.Contains(id));
            p2.ActiveCreaturesByID.RemoveAll(id => recently_dead.Contains(id));
            allCreatures.RemoveAll(c => recently_dead.Contains(c.ID));

            // Очищуємо ініціативну чергу від мертвих істот
            var tempQueue = new PriorityQueue<Creature, int>();
            while (initiativeQueue.Count > 0)
            {
                var creature = initiativeQueue.Dequeue();
                if (!recently_dead.Contains(creature.ID))
                {
                    tempQueue.Enqueue(creature, -creature.Initiative);
                }
            }
            initiativeQueue = tempQueue;
        }

        void EnqueueCreaturesToInitiativeQueue(List<Creature> creatures, PriorityQueue<Creature, int> queue)
        {
            foreach (var creature in creatures)
            {
                queue.Enqueue(creature, -creature.Initiative); // -Initiative для сортування за спаданням
            }
        }

    }

}

*/




/*

using Model;

namespace Controller;

public interface ITurnManager
{

}

public class TurnManager : ITurnManager
{
    private Creature currentCreature;
    public bool TurnFinished;

    public TurnManager(Creature creature)
    {
        currentCreature = creature;
        TurnFinished = false;
    }

    public void PlayTurn(Creature target)
    {
        Attack(target);
    }

    public void PlayTurn(Grid grid)
    {
        Move(null, grid);
    }

    public void PlayTurn()
    {
        Skip();
    }

    private void Attack(Creature target)
    {
        currentCreature.Punch(target);
        if (currentCreature.MovementRemaining < 1)
        {
            TurnFinished = true;
        }
        // OnTurnComplete?.Invoke();
        // Console.WriteLine($"{currentCreature.GetType().Name} атакував {target.GetType().Name}!");
    }

    private void Skip()
    {
        TurnFinished = true;
        // OnTurnComplete?.Invoke();
        // Console.WriteLine($"{currentCreature.GetType().Name} атакував {target.GetType().Name}!");
    }

    private void Move(Cell targetCell, Grid grid)
    {
        var reachableCells = grid.GetReachableCellsByCreatureId(currentCreature.ID, currentCreature.MovementRemaining);

        if (reachableCells.Contains(targetCell))
        {
            var currentCell = grid.Cells.Cast<Cell>().First(c => c.CellTaker == currentCreature);
            currentCell.MoveAway(targetCell);

            currentCreature.MovementRemaining = 0;
            // Console.WriteLine($"{currentCreature.GetType().Name} перемістився на нову клітинку!");
            // OnTurnComplete?.Invoke();
        }
        else
        {
            Console.WriteLine("Ця клітинка недосяжна для переміщення.");
        }
    }
}



*/