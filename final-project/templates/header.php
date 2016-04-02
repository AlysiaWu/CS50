<!DOCTYPE html>

<html>

    <head>

        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>myLibrary: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>myLibrary</title>
        <?php endif ?>

        <script src="/js/jquery-1.11.1.min.js"></script>
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

    </head>

    <body>

        <div class="container">

            <div id="top">
                <div id="title">
                    <a href="/">myLibrary</a>
                </div>
                <div id="menu">
                    <a href="mybooks.php">myBooks</a>
                    <a href="addbook.php">+Book</a>
                    <a href="search.php">Search</a>
                    <a href="logout.php">Logout</a>
                </div> 
            </div>

            <div id="middle">
