using UnityEngine;

public class Ingredient : MonoBehaviour
{
    private CookingGame gameManager;

    public void Setup(string name, CookingGame manager)
    {
        gameManager = manager;
        GetComponentInChildren<TextMesh>().text = name; // Nama bahan
    }

    private void OnMouseDown()
    {
        gameManager.ChopIngredient(gameObject);
    }
}
