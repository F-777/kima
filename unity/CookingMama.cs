using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CookingGame : MonoBehaviour
{
    public Text scoreText;
    public Text timerText;
    public GameObject ingredientPrefab;
    public Transform ingredientContainer;

    private int score = 0;
    private float timer = 30f; // 30 seconds
    private bool gameOver = false;

    void Start()
    {
        SpawnIngredients();
        UpdateScoreText();
    }

    void Update()
    {
        if (!gameOver)
        {
            timer -= Time.deltaTime;
            timerText.text = "Time Left: " + Mathf.Ceil(timer) + "s";

            if (timer <= 0)
            {
                GameOver();
            }
        }
    }

    void SpawnIngredients()
    {
        string[] ingredientNames = { "Carrot", "Tomato", "Potato" };

        foreach (string name in ingredientNames)
        {
            GameObject ingredient = Instantiate(ingredientPrefab, ingredientContainer);
            ingredient.GetComponent<Ingredient>().Setup(name, this);
        }
    }

    public void ChopIngredient(GameObject ingredient)
    {
        if (gameOver) return;

        Destroy(ingredient);
        score += 10;
        UpdateScoreText();
    }

    void UpdateScoreText()
    {
        scoreText.text = "Score: " + score;
    }

    void GameOver()
    {
        gameOver = true;
        timerText.text = "Time's Up!";
        Debug.Log("Game Over! Final Score: " + score);
    }
}
