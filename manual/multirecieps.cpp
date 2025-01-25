// Variabel untuk jumlah resep per level
int recipesPerLevel = 2;
int currentRecipeIndex = 0;

// Update jika resep selesai
if (recipeCompleted) {
    currentRecipeIndex++;
    if (currentRecipeIndex >= recipesPerLevel) {
        // Semua resep selesai, naik level
        level++;
        currentRecipeIndex = 0;
        recipesPerLevel++;
        spawnIngredients();
    } else {
        // Lanjutkan ke resep berikutnya
        spawnIngredients();
    }
}
