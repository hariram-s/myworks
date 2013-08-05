<!DOCTYPE html>
<html>
  <head>
    <title>Billing application</title>
    <script type="text/javascript" src="js/utility.js"></script>
    <script type="text/javascript" src="js/ajax.js"></script>
    <script type="text/javascript" src="js/script.js"></script>
  </head>
  <body>
    <div id="content-wrapper">
      <div id="header">
        <h2><?php echo $this->title; ?></h2>
      </div>
      <?php if (!empty($this->main_links)) : ?>
      <div>
        <ul>
        <?php foreach ($this->main_links as $link) : ?>
          <li>
            <a href="<?php echo $link['href'];?>"><?php echo $link['title']; ?></a>
          </li>
        <?php endforeach; ?>
        </ul>
      </div>
      <?php endif; ?>
      <?php if (!empty($this->links)) : ?>
      <div>
        <ul>
        <?php foreach ($this->links as $link) : ?>
          <li>
            <a href="<?php echo $link['href'];?>"><?php echo $link['title']; ?></a>
          </li>
        <?php endforeach; ?>
        </ul>
      </div>
      <?php endif; ?>
      <?php if(!empty ($this->bill_no)) : ?> 
      <div id="bill_no">
        <?php echo $this->bill_no; ?>
      </div>
      <?php endif; ?>
      <?php if(!empty ($this->forms)) : ?> 
      <div id="form">
        <?php echo $this->forms; ?>
      </div>
      <?php endif; ?>
      <?php if(!empty ($this->tables)) : ?>
      <div id="table">
        <?php echo $this->tables; ?>
      </div>
      <?php endif; ?>
    </div>
    <script type="text/javascript">
      initialize();
    </script>
  </body>
</html>  
